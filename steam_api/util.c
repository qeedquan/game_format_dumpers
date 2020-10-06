#include "steam.h"

#if defined(_WIN32)
#define makedir(x) _mkdir(x)

char *
dirname(char *path)
{
	char drv[PATH_MAX], dir[PATH_MAX];

	if (path == NULL)
		return ".";
	_splitpath_s(path, drv, sizeof(drv), dir, sizeof(dir), NULL, 0, NULL, 0);
	snprintf(path, strlen(path) + 1, "%s%s", drv, dir);
	return path;
}

char *
basename(char *path)
{
	char base[PATH_MAX], ext[PATH_MAX];

	if (path == NULL)
		return ".";
	_splitpath_s(path, NULL, 0, NULL, 0, base, sizeof(base), ext, sizeof(ext));
	snprintf(path, strlen(path) + 1, "%s%s", base, ext);
	return path;
}

uint64
msticks(void)
{
	return GetTickCount64() / 1000;
}

#else
#define makedir(x) mkdir(x, 0755)

uint64
msticks(void)
{
	struct timespec t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec * 1000) + (t.tv_nsec / 1000000);
}

#endif

void *
xrealloc(void *ptr, size_t size)
{
	ptr = realloc(ptr, size);
	if (ptr == NULL)
		abort();
	return ptr;
}

#define MUL_NO_OVERFLOW ((size_t)1 << (sizeof(size_t) * 4))

void *
reallocarray(void *optr, size_t nmemb, size_t size)
{
	if ((nmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) &&
	    nmemb > 0 && SIZE_MAX / nmemb < size) {
		errno = ENOMEM;
		return NULL;
	}
	return realloc(optr, size * nmemb);
}

void *
xreallocarray(void *optr, size_t nmemb, size_t size)
{
	void *ptr;

	ptr = reallocarray(optr, nmemb, size);
	if (ptr == NULL)
		abort();
	return ptr;
}

int
xstat(const char *filename, struct stat *st)
{
	char path[PATH_MAX * 2];

	snprintf(path, sizeof(path), "%s/%s", ctx.rootDir, filename);
	mkdirp(dirname(path));
	snprintf(path, sizeof(path), "%s/%s", ctx.rootDir, filename);
	return stat(path, st);
}

FILE *
xfopen(const char *filename, const char *mode)
{
	char path[PATH_MAX * 2];
	FILE *fp;

	snprintf(path, sizeof(path), "%s/%s", ctx.rootDir, filename);
	mkdirp(dirname(path));
	snprintf(path, sizeof(path), "%s/%s", ctx.rootDir, filename);
	fp = fopen(path, mode);
	if (!fp)
		xlogf("%s: %s\n", path, strerror(errno));
	return fp;
}

void
mkdirp(char *s)
{
	char *p;

	for (p = strchr(s + 1, '/'); p; p = strchr(p + 1, '/')) {
		*p = 0;
		makedir(s);
		*p = '/';
	}
	makedir(s);
}

CSteamFile *
getFileListing(const char *dir, int32 *numFiles)
{
#ifdef _WIN32
	char path[MAX_PATH * 2];
	WIN32_FIND_DATA ffd;
	HANDLE hFind;
	CSteamFile *files, *file;

	files = NULL;
	*numFiles = 0;

	snprintf(path, sizeof(path), "%s/*", dir);
	hFind = FindFirstFile(path, &ffd);
	if (hFind == INVALID_HANDLE_VALUE) {
		return files;
	}

	do {
		if (!strcmp(ffd.cFileName, ".") || !strcmp(ffd.cFileName, ".."))
			continue;

		files = xreallocarray(files, (*numFiles + 1), sizeof(*files));

		file = &files[*numFiles];
		snprintf(file->path, sizeof(file->path), "%s/%s", dir, ffd.cFileName);
		file->isDir = (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
		file->size = ffd.nFileSizeLow;

		(*numFiles)++;
	} while (FindNextFile(hFind, &ffd) != 0);

	return files;

#else
	CSteamFile *files, *file;
	struct dirent **namelist, *ent;
	struct stat st;
	int i, n;

	*numFiles = 0;

	n = scandir(dir, &namelist, NULL, alphasort);
	if (n < 0)
		return NULL;
	files = malloc(sizeof(*files) * n);
	for (i = 0; i < n; i++) {
		file = &files[*numFiles];
		ent = namelist[i];

		if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
			continue;

		snprintf(file->path, sizeof(file->path), "%s/%s", dir, ent->d_name);
		file->isDir = (ent->d_type & DT_DIR) != 0;
		stat(file->path, &st);
		file->size = st.st_size;
		(*numFiles)++;
		free(ent);
	}
	free(namelist);

	return files;
#endif
}

CSteamFile *
getAllFileListingRec(const char *dir, int32 *numFiles)
{
	CSteamFile *files, *tmpFiles, *subFiles;
	int32 i, j, count, subCount;

	*numFiles = 0;

	files = NULL;
	tmpFiles = getFileListing(dir, &count);
	for (i = 0; i < count; i++) {
		if (tmpFiles[i].isDir) {
			subFiles = getAllFileListingRec(tmpFiles[i].path, &subCount);
			for (j = 0; j < subCount; j++) {
				files = xreallocarray(files, *numFiles + 1, sizeof(*files));
				files[*numFiles] = subFiles[j];
				(*numFiles)++;
			}
			free(subFiles);
		} else {
			files = xreallocarray(files, *numFiles + 1, sizeof(*files));
			files[*numFiles] = tmpFiles[i];
			(*numFiles)++;
		}
	}
	free(tmpFiles);

	return files;
}

CSteamFile *
getAllFileListing(const char *dir, int32 *numFiles)
{
	CSteamFile *files;
	char path[PATH_MAX], *ptr;
	int32 i;

	files = getAllFileListingRec(dir, numFiles);
	for (i = 0; i < *numFiles;) {
		if (files[i].isDir) {
			memmove(&files[i], &files[i + 1], sizeof(CSteamFile) * (*numFiles - i));
			(*numFiles)--;
			continue;
		}

		ptr = strchr(files[i].path, '/');
		if (ptr) {
			ptr++;
			snprintf(path, sizeof(path), "%s", ptr);
			snprintf(files[i].path, sizeof(files[i].path), "%s", path);
		}
		i++;
	}
	return files;
}

int
parseSteamVersion(const char *s)
{
	size_t i;

	for (i = 0; s[i]; i++) {
		if (isdigit(s[i]))
			return atoi(&s[i]);
	}
	return 0;
}

void
getEnvStr(char *buf, size_t len, const char *env, const char *def)
{
	char *p;

	p = getenv(env);
	if (p)
		snprintf(buf, len, "%s", p);
	else
		snprintf(buf, len, "%s", def);
}

int
getEnvInt(const char *env, int def)
{
	int val;
	char *p;

	p = getenv(env);
	if (p)
		val = atoi(p);
	else
		val = def;
	return val;
}

#if defined(_WIN32)

DWORD
getRegDWORD(HKEY hkey, const char *subkey, const char *data, DWORD def)
{
	HKEY key;
	DWORD type, val, len;
	BYTE buf[32];

	len = sizeof(buf);
	if (RegOpenKeyA(hkey, subkey, &key) != ERROR_SUCCESS)
		return def;
	if (RegQueryValueExA(key, data, NULL, &type, buf, &len) != ERROR_SUCCESS)
		return def;
	RegCloseKey(key);

	if (type != REG_DWORD)
		val = def;
	else
		val = atoi((char *)buf);
	return val;
}

#endif