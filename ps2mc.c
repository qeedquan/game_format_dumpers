// reads ps2 memory card as a fuse filesystem
// write not supported
// cc -o ps2mc ps2mc.c `pkg-config fuse glib-2.0 --cflags --libs` -ggdb -g3 -Wall -pedantic -lm -std=gnu11
// ./ps2mc mount -f Mcd001.ps2
#define FUSE_USE_VERSION 30
#include <fuse.h>
#include <glib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include <time.h>

enum
{
    DF_READ      = 1<<0,
    DF_WRITE     = 1<<1,
    DF_EXEC      = 1<<2,
    DF_PROTECTED = 1<<3,
    DF_FILE      = 1<<4,
    DF_DIRECTORY = 1<<5,
    DF_IGN1      = 1<<6,
    DF_IGN2      = 1<<7,
    DF_IGN3      = 1<<8,
    DF_CREAT     = 1<<9,
    DF_0400      = 1<<10,
    DF_POCKETSTN = 1<<11,
    DF_PSX       = 1<<12,
    DF_HIDDEN    = 1<<13,
    DF_INT3      = 1<<14,
    DF_EXISTS    = 1<<15
};

enum
{
    CF_USE_ECC      = 1<<0,
    CF_BAD_BLOCK    = 1<<3,
    CF_ERASE_ZEROES = 1<<4
};

#define CL_ALLOCATED 0x80000000
#define CL_MASK      0x7FFFFFFF
#define CL_EOF       0xFFFFFFFF

struct ps2mc
{
    GMappedFile *file;
    GNode       *tree;

    guint8  **clusters;
    guint8  **pages;
    guint8  **eccpages;
    guint32   ifc[32];

    gchar    version[32];
    guint8   flag;
    guint16  eccsize;
    guint16  pagesize;
    guint16  pages_per_cluster;
    guint16  pages_per_block;
    guint16  total_clusters;
    guint16  alloc_offset;
    guint16  root_cluster;
    guint32  entries_per_cluster;
    guint32  cluster_size;
};

struct file
{
    guint32  mode;
    guint32  length;
    guint8   created[8];
    guint32  cluster;
    guint32  dir_entry;
    guint8   modified[8];
    guint32  attr;
    gchar    name[32];
    GArray  *clusters;
};

struct ps2mc *ps2mc_open  (const gchar*);
void          ps2mc_close (struct ps2mc*);

int   ps2mc_getattr    (const char*, struct stat*);
int   ps2mc_opendir    (const char*, struct fuse_file_info*);
int   ps2mc_readdir    (const char*, void*, fuse_fill_dir_t, off_t,
                        struct fuse_file_info*);
int   ps2mc_releasedir (const char*, struct fuse_file_info*);
int   ps2mc_read       (const char*, char*, size_t, off_t,
                        struct fuse_file_info*);
int   ps2mc_ioctl      (const char*, int, void*,
                        struct fuse_file_info*, unsigned int, void*);
int   ps2mc_mkdir      (const char*, mode_t);
void *ps2mc_init       (struct fuse_conn_info*);
void  ps2mc_destroy    (void*);

static void init_table (void);

static const struct fuse_operations opers =
{
    .getattr    = ps2mc_getattr,
    .opendir    = ps2mc_opendir,
    .readdir    = ps2mc_readdir,
    .releasedir = ps2mc_releasedir,
    .read       = ps2mc_read,
    .ioctl      = ps2mc_ioctl,
    .mkdir      = ps2mc_mkdir,
    .init       = ps2mc_init,
    .destroy    = ps2mc_destroy
};

int main(int argc, char *argv[])
{
    struct ps2mc *c;
    char *fn;

    init_table();

    if (argc < 3)
    {
        g_print("usage: <mount> <options> <file>\n");
        return 1;
    }

    fn = argv[argc-1];
    argc--;
    c = ps2mc_open(fn);
    if (!c)
        return 1;

    return fuse_main(argc, argv, &opers, c);
}

static guint16 read16le(const guint8 *b)
{
    return (guint16)b[0] | ((guint16)b[1] << 8);
}

static guint32 read32le(const guint8 *b)
{
    return (guint32)b[0] | ((guint32)b[1] << 8) |
           ((guint32)b[2] << 16) | ((guint32)b[3] << 24);
}

static guint8 parity_table[256];
static guint8 parity_column_mask[256];

static guint8 get_parity(guint8 v)
{
    v = (v ^ (v >> 1));
    v = (v ^ (v >> 2));
    v = (v ^ (v >> 4));
    return v;
}

static void init_table()
{
    static const guint8 cpmask[] =
    {
        0x55, 0x33, 0x0F, 0x00, 0xAA, 0xCC, 0xF0
    };

    gint i, j;
    guint32 mask;

    for (i = 0; i < 256; i++)
        parity_table[i] = get_parity(i);

    for (i = 0; i < 256; i++)
    {
        mask = 0;
        for (j = 0; j < G_N_ELEMENTS(cpmask); j++)
            mask |= (guint32)parity_table[i&cpmask[j]] << j;

        parity_column_mask[i] = mask & 0xFF;
    }
}

void gen_hamming_code(guint8 *dst, guint8 *src, gint size)
{
    guint8 column_parity, line_parity[2], v;
    gint i;

    column_parity = 0x77;
    line_parity[0] = 0x7F;
    line_parity[1] = 0x7F;

    for (i = 0; i < size; i++)
    {
        v = src[i];
        column_parity ^= parity_column_mask[v];
        if (parity_table[v])
        {
            line_parity[0] ^= ~i & 0xFF;
            line_parity[1] ^= i & 0xFF;
        }
    }

    dst[0] = column_parity;
    dst[1] = line_parity[0] & 0x7F;
    dst[2] = line_parity[1];
}

static void free_file(struct file *f)
{
    g_return_if_fail(f);
    g_array_free(f->clusters, TRUE);
    g_free(f);
}

static time_t convert_time(const guint8 *b)
{
    time_t t;
    struct tm tm, result;

    memset(&tm, 0, sizeof(tm));
    tm.tm_sec = b[1];
    tm.tm_min = b[2];
    tm.tm_hour = b[3];
    tm.tm_mday = b[4];
    tm.tm_mon = b[5];
    tm.tm_year = read16le(b+6) - 1900;
    t = mktime(&tm);
    gmtime_r(&t, &result);
    return mktime(&result);
}

static struct file *get_file_info(struct ps2mc *c, guint32 page)
{
    guint32 off;
    int error;
    guint8 *b;
    struct file *f;
    guint32 n;
    guint i;
    gboolean *collision;
    guint32 fat_offset, indirect_index,
            indirect_offset, dbl_indirect_index,
            indirect_cluster_num, fat_cluster_num;
    guint8 *indirect_cluster, *fat_cluster;

    error = FALSE;
    f = g_new0(struct file, 1);
    f->clusters = g_array_new(FALSE, TRUE, sizeof(guint32));
    b = c->pages[c->alloc_offset*2 + page];

    f->mode = read32le(b);
    f->length = read32le(b+0x04);
    f->cluster = read32le(b+0x10);
    f->dir_entry = read32le(b+0x14);
    f->attr = read32le(b+0x20);
    memcpy(f->created, b+0x08, 8);
    memcpy(f->modified, b+0x18, 8);
    memcpy(f->name, b+0x40, 32);
    f->name[31] = '\0';

    collision = g_new0(gboolean, c->total_clusters);

    n = f->cluster | CL_ALLOCATED;
    for (;;)
    {
        if (n == CL_EOF)
            break;

        if (n & CL_ALLOCATED)
        {
            n &= CL_MASK;
            if (n >= c->total_clusters)
            {
                g_warning("%s: out of bound cluster: %u\n", f->name, n);
                goto error;
            }

            g_array_append_val(f->clusters, n);
        }
        else
        {
            g_warning("%s: encountered corrupted cluster: %u\n", f->name, n);
            goto error;
        }

        if (collision[n])
        {
            g_print("%s: encountered collision: %u", f->name, n);
            goto error;
        }
        collision[n] = TRUE;

        fat_offset = n % c->entries_per_cluster;
        indirect_index = n / c->entries_per_cluster;

        indirect_offset = indirect_index % c->entries_per_cluster;
        dbl_indirect_index = indirect_index / c->entries_per_cluster;

        indirect_cluster_num = c->ifc[dbl_indirect_index];
        indirect_cluster = c->clusters[indirect_cluster_num];

        off = indirect_offset * 4;
        off += (off / c->pagesize) * c->eccsize;

        fat_cluster_num = read32le(indirect_cluster + off);
        fat_cluster = c->clusters[fat_cluster_num];

        off = fat_offset * 4;
        off += (off / c->pagesize) * c->eccsize;
        n = read32le(fat_cluster + off);
    }

done:
    g_print("\nFile %s:\n", f->name);
    g_print("Exist: %d\n", f->mode & DF_EXISTS);
    g_print("Size: %d\n", f->length);
    g_print("Cluster: ");
    for (i = 0; i < f->clusters->len; i++)
    {
        n = g_array_index(f->clusters, guint32, i);
        g_print("%u ", n);
    }
    g_print("\n");
    g_print("\n\n");

    if (error)
    {
        free_file(f);
        f = NULL;
    }

    g_free(collision);
    return f;

error:
    error = TRUE;
    goto done;
}

static int read_file(struct ps2mc *c, struct file *f,
                     guint8 *buf, size_t size, off_t off)
{
    off_t offset;
    int nread;
    guint i;
    guint32 j, n;
    size_t len;
    uint8_t *p;

    nread = 0;

    if (size > f->length)
        size = f->length;

    offset = off % c->cluster_size;
    for (i = off / c->cluster_size; i < f->clusters->len; i++)
    {
        n = g_array_index(f->clusters, guint32, i);
        for (j = offset / c->pagesize; j < c->pages_per_cluster; j++)
        {
            p = c->pages[(c->alloc_offset + n) * c->pages_per_cluster + j];
            len = c->pagesize - offset;
            if (size < len)
                len = size;

            if ((INT_MAX - len) < nread)
                len = INT_MAX - nread;

            memcpy(buf+(off_t)nread, p+(off_t)offset, len);
            nread += len;

            size -= len;
            if (size == 0 || nread == INT_MAX)
                goto out;

            offset = 0;
        }
    }

out:
    return nread;
}

static void build_tree_rec(struct ps2mc *c, GNode *parent)
{
    GNode *node;
    struct file *f, *p;
    guint32 i, page;

    p = parent->data;
    if (p->mode & DF_FILE)
        return;

    for (i = 0; i < p->length; i++)
    {
        page = g_array_index(p->clusters, guint32, i/c->pages_per_cluster);
        page = page * 2 + (i % c->pages_per_cluster);

        f = get_file_info(c, page);
        if (!f)
            continue;

        node = g_node_new(f);

        g_node_insert(parent, i, node);

        if (!strcmp(f->name, ".") || !strcmp(f->name, ".."))
            continue;

        if (f->mode & DF_DIRECTORY)
            build_tree_rec(c, node);
    }
}

static GNode *build_tree(struct ps2mc *c)
{
    GNode *root;
    struct file *f;

    f = get_file_info(c, c->root_cluster*2);
    if (!f)
        return NULL;

    g_strlcpy(f->name, "/", G_N_ELEMENTS(f->name));
    root = g_node_new(f);
    build_tree_rec(c, root);

    return root;
}

static GNode *get_path(GNode *root, const gchar *path)
{
    struct file *f;
    GNode *node, *child;
    gchar **tokens;
    gsize i, j;

    tokens = g_strsplit(path, "/", 0);
    node = root;
    for (i = 0; tokens[i]; i++)
    {
        if (tokens[i][0] == '\0')
            continue;

        for (j = 0; ; j++)
        {
            child = g_node_nth_child(node, j);
            if (!child)
            {
                node = NULL;
                goto out;
            }

            f = child->data;
            if (!strcmp(f->name, tokens[i]))
            {
                node = child;
                break;
            }
        }
    }

out:
    g_strfreev(tokens);
    return node;
}

static const gchar *magic = "Sony PS2 Memory Card Format ";
static const int eccsize = 16;
static const int max_pages_per_block = 16;

struct ps2mc *ps2mc_open(const gchar *fn)
{
    off_t off;
    GError *error;
    struct ps2mc *c;
    guint8 *b;
    guint i;

    c = g_new0(struct ps2mc, 1);

    error = NULL;
    c->file = g_mapped_file_new(fn, TRUE, &error);
    if (error)
    {
        g_warning("%s\n", error->message);
        goto error;
    }

    b = (guint8*)g_mapped_file_get_contents(c->file);

    if (memcmp(b, magic, 28))
    {
        g_warning("invalid magic encountered");
        goto error;
    }

    memcpy(c->version, b+0x1C, 32);
    c->version[31] = '\0';
    c->pagesize = read16le(b+0x28);
    c->pages_per_cluster = read16le(b+0x2A);
    c->pages_per_block = read16le(b+0x2C);
    c->total_clusters = read16le(b+0x30);
    c->alloc_offset = read16le(b+0x34);
    c->root_cluster = read16le(b+0x3C);
    c->flag = b[0x151];
    c->cluster_size = c->pagesize * c->pages_per_cluster;
    c->entries_per_cluster = c->pagesize * c->pages_per_cluster / 4;

    if (c->flag & CF_USE_ECC)
        c->eccsize = eccsize;

    c->clusters = g_new0(guint8*, c->total_clusters);
    c->pages = g_new0(guint8*, c->pages_per_cluster * c->total_clusters);
    c->eccpages = g_new0(guint8*, c->pages_per_cluster * c->total_clusters);

    for (i = 0; i < c->total_clusters; i++)
    {
        off = i * (c->cluster_size + (c->eccsize*c->pages_per_cluster));
        c->clusters[i] = b+off;
    }

    for (i = 0; i < c->total_clusters * c->pages_per_cluster; i++)
    {
        off = i * (c->pagesize + c->eccsize);
        c->pages[i] = b+off;

        off = (i+1) * c->pagesize + (c->eccsize * i);
        c->eccpages[i] = b+off;
    }

    for (i = 0; i < 32; i++)
        c->ifc[i] = read32le(b + 0x50+i*4);

    g_print("version: %s\n", c->version);
    g_print("page size: %d\n", c->pagesize);
    g_print("entries per cluster: %d\n", c->entries_per_cluster);
    g_print("pages per cluster: %d\n", c->pages_per_cluster);
    g_print("pages per block: %d\n", c->pages_per_block);
    g_print("total clusters: %d\n", c->total_clusters);
    g_print("alloc offset: %d\n", c->alloc_offset);
    g_print("root cluster: %d\n", c->root_cluster);

    c->tree = build_tree(c);

    return c;

error:
    g_error_free(error);
    ps2mc_close(c);
    return NULL;
}

void ps2mc_close(struct ps2mc *c)
{
    g_return_if_fail(c);

    if (c->file)
        g_mapped_file_unref(c->file);
    g_free(c->clusters);
    g_free(c->pages);
    g_free(c->eccpages);
    g_free(c);
}

void *ps2mc_init(struct fuse_conn_info *info)
{
    return fuse_get_context()->private_data;
}

void ps2mc_destroy(void *data)
{
    g_print("destroy\n");
    ps2mc_close(data);
}

int ps2mc_getattr(const char *path, struct stat *stat)
{
    GNode *node;
    struct file *f;
    struct ps2mc *c;

    g_print("getattr: %s\n", path);

    c = fuse_get_context()->private_data;
    if (!c)
        return -EHOSTDOWN;

    node = get_path(c->tree, path);
    if (!node)
        return -ENOENT;

    f = node->data;
    if (f->mode & DF_FILE)
        stat->st_mode |= S_IFREG;
    else if (f->mode & DF_DIRECTORY)
        stat->st_mode |= S_IFDIR;

    if (f->mode & DF_READ)
        stat->st_mode |= S_IRUSR|S_IRGRP|S_IROTH;
    if (f->mode & DF_WRITE)
        stat->st_mode |= S_IWUSR|S_IWGRP|S_IWOTH;
    if (f->mode & DF_EXEC)
        stat->st_mode |= S_IXUSR|S_IXGRP|S_IXOTH;

    stat->st_ctime = convert_time(f->created);
    stat->st_mtime = convert_time(f->modified);
    stat->st_atime = time(NULL);

    stat->st_size = f->length;
    stat->st_uid = getuid();
    stat->st_gid = getgid();
    stat->st_blksize = c->pagesize;
    stat->st_blocks = ceil(f->length / 512.0);
    return 0;
}

int ps2mc_opendir(const gchar *dir, struct fuse_file_info *fi)
{
    struct file *f;
    struct ps2mc *c;
    GNode *node;

    g_print("opendir: %s\n", dir);

    c = fuse_get_context()->private_data;
    if (!c)
        return -EHOSTDOWN;

    node = get_path(c->tree, dir);
    if (!node)
        return -ENOENT;

    f = node->data;
    if (!(f->mode & DF_DIRECTORY))
        return -ENOTDIR;

    fi->fh = (uintptr_t)node->children;
    return 0;
}

int ps2mc_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
                  struct fuse_file_info *fi)
{
    struct file *f;
    GNode *node;

    g_print("readdir: %s\n", path);
    node = (GNode*)fi->fh;
    if (!node)
        return -ENOENT;

    do
    {
        f = node->data;
        filler(buf, f->name, NULL, 0);
        node = node->next;
    } while (node);

    return 0;
}

int ps2mc_releasedir(const char *path, struct fuse_file_info *fi)
{
    g_print("releasedir: %s\n", path);
    return 0;
}

int ps2mc_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    struct file *f;
    struct ps2mc *c;
    GNode *node;

    g_print("read: %s size=%lu offset=%lu\n", path, size, offset);

    c = fuse_get_context()->private_data;
    if (!c)
        return -EHOSTDOWN;

    node = get_path(c->tree, path);
    if (!node)
        return -ENOENT;

    f = node->data;
    if (f->mode & DF_DIRECTORY)
        return -EISDIR;

    return read_file(c, f, (guint8*)buf, size, offset);
}

int ps2mc_ioctl(const char *path, int cmd, void *arg,
                struct fuse_file_info *fi, unsigned int flags, void *data)
{
    g_print("ioctl: %s cmd=%d flags=%u\n", path, cmd, flags);
    return 0;
}

int ps2mc_mkdir(const char *path, mode_t mode)
{
    struct file *f;
    struct ps2mc *c;
    GNode *node;

    c = fuse_get_context()->private_data;
    if (!c)
        return -EHOSTDOWN;

    g_print("mkdir: %s\n", path);
    node = get_path(c->tree, path);
    if (node)
        return -EEXIST;

    return 0;
}

