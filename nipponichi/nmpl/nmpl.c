#include <windows.h>
#include "ioutil.h"
#include "nmpl.h"

#define nelem(x) (sizeof(x) / sizeof(x[0]))

typedef struct {
	HANDLE nmpllib;
	Compress compress;
} GC;

GC gc;

void
usage(void)
{
	printf("Usage: [options] <command> <input> <output>\n");
	printf("  -h  show this message\n");
	printf("\n");
	printf("Available commands:\n");
	printf("  d <input> <output>                decompress input and write to output\n");
	printf("  e <algorithm> <input> <output>    compress input and write to output\n");
	printf("\n");
	exit(2);
}

void
parseflags(int *argc, char ***argv)
{
	int i, j;

	for (i = 1; i < *argc; i++) {
		if ((*argv)[i][0] != '-')
			break;

		for (j = 1; (*argv)[i][j]; j++) {
			switch ((*argv)[i][j]) {
			case 'h':
				usage();
				break;
			}
		}
	}

	*argc -= i;
	*argv += i;
}

void
init(void)
{
	HANDLE nmpllib;
	Compress compress;
	voidfn lzlibinit;

	SetDllDirectoryA(NULL);
	nmpllib = LoadLibraryA("NmplDLL.dll");
	if (!nmpllib)
		fatal("Failed to load NMPL DLL: %d", GetLastError());

	memset(&compress, 0, sizeof(compress));
	lzlibinit = (voidfn)GetProcAddress(nmpllib, "?lzLibInitialize@CCompress@Core@Nmpl@@SAXXZ");
	compress.vtable.constructor = (Compress_Constructor)GetProcAddress(nmpllib, "??0CCompress@Core@Nmpl@@QEAA@PEAEI@Z");
	compress.vtable.encode = (Compress_Encode)GetProcAddress(nmpllib, "?encode@CCompress@Core@Nmpl@@QEAAXPEBD@Z");
	compress.vtable.decode = (Compress_Decode)GetProcAddress(nmpllib, "?decode@CCompress@Core@Nmpl@@QEAAXPEAXH@Z");
	if (!lzlibinit || !compress.vtable.constructor || !compress.vtable.encode || !compress.vtable.decode)
		fatal("Failed to load NMPL library functions");

	lzlibinit();

	gc.nmpllib = nmpllib;
	gc.compress = compress;
}

void
mkcio(Compress *compress, char **args, int numargs, FILE **fin, FILE **fout, void **data, size_t *size)
{
	FILE *in, *out;
	void *buf;

	in = stdin;
	out = stdout;
	switch (numargs) {
	case 2:
		out = fopen(args[1], "wb");
		// fallthrough
	case 1:
		in = fopen(args[0], "rb");
		break;
	case 0:
		break;
	default:
		fatal("Invalid number of arguments: got %d", numargs);
		break;
	}

	if (in == NULL || out == NULL)
		fatal("Error opening input/output files: %s", strerror(errno));

	buf = freadall(in, size);
	if (!in)
		fatal("Failed to read input");

	compress->vtable.constructor(compress, buf, 0);

	*fin = in;
	*fout = out;
	*data = buf;
}

void
decode(Compress *compress, char **args, int numargs)
{
	FILE *fin, *fout;
	void *data;
	size_t size;

	mkcio(compress, args, numargs, &fin, &fout, &data, &size);
	compress->vtable.decode(compress, NULL, 0);
	if (fwrite(compress->output, compress->output_size, 1, fout) != 1)
		fatal("Failed to write to output: %s", strerror(errno));

	fclose(fin);
	fclose(fout);
}

void
encode(Compress *compress, char **args, int numargs)
{
	FILE *fin, *fout;
	void *data;
	size_t size;

	if (numargs < 1)
		fatal("Missing encoding type parameter");

	mkcio(compress, args + 1, numargs - 1, &fin, &fout, &data, &size);
	compress->output = data;
	compress->output_size = size;
	compress->vtable.encode(compress, args[0]);
	if (fwrite(compress->input, compress->input_size, 1, fout) != 1)
		fatal("Failed to write to output: %s", strerror(errno));

	fclose(fin);
	fclose(fout);
}

void
execute(const char *name, char **args, int numargs)
{
	Compress *compress;

	compress = &gc.compress;
	if (!strcmp(name, "d"))
		decode(compress, args, numargs);
	else if (!strcmp(name, "e"))
		encode(compress, args, numargs);
	else
		fatal("Unknown command '%s'", name);
}

void
cleanup(void)
{
	FreeLibrary(gc.nmpllib);
}

int
main(int argc, char *argv[])
{
	parseflags(&argc, &argv);
	if (argc < 1)
		usage();

	init();
	execute(argv[0], argv + 1, argc - 1);
	cleanup();

	return 0;
}
