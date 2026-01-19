#pragma once

#define nelem(x) (sizeof(x) / sizeof(x[0]))

typedef struct {
	char key[128];
	char val[128];
} KV;

#if defined(__GNUC__)
#if defined(_WIN32)
#define PRINTF_LIKE __attribute__((__format__(__MINGW_PRINTF_FORMAT, 1, 2)))
#else
#define PRINTF_LIKE __attribute__((format(printf, 1, 2)))
#endif
#else
#define PRINTF_LIKE
#endif

#ifdef WIN32
#define stat _stat
#endif

char *cleanname(char *name);

void hexdump(void *buf, size_t len);
void trimSpace(char *str);

int saveKV(const char *filename, KV *kv, size_t kvlen);
int loadKV(const char *filename, KV *kv, size_t kvcap, size_t *kvlen);
KV *lookupKV(KV *kv, size_t kvlen, const char *key);

int xstat(const char *filename, struct stat *st);
FILE *xfopen(const char *filename, const char *mode);
void *xrealloc(void *ptr, size_t size);
void *xcalloc(size_t nmemb, size_t size);
void *xreallocarray(void *optr, size_t nmemb, size_t size);
void mkdirp(char *path);

CSteamFile *getAllFileListing(const char *dir, int32 *numFiles);

int parseSteamVersion(const char *s);

void getEnvStr(char *buf, size_t len, const char *env, const char *def);
int getEnvInt(const char *env, int def);

#if defined(_WIN32)
DWORD getRegDWORD(HKEY hkey, const char *subkey, const char *data, DWORD def);
char *basename(char *path);
char *dirname(char *path);
#define acquireLock EnterCriticalSection
#define releaseLock LeaveCriticalSection
#else
#define acquireLock pthread_mutex_lock
#define releaseLock pthread_mutex_unlock
#endif

uint64 msticks(void);

PRINTF_LIKE static inline void
xprintf(const char *fmt, ...)
{
	char str[4096];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(str, sizeof(str), fmt, ap);
	va_end(ap);

	fprintf(stdout, "%s", str);
	fflush(stdout);
	if (ctx.logFile) {
		fprintf(ctx.logFile, "%s", str);
		fflush(ctx.logFile);
	}
}

PRINTF_LIKE static inline void
xlogf(const char *fmt, ...)
{
	uint64 curtick, maxtick, delta;
	char str[4096];
	bool found;
	va_list ap;
	size_t i, idx;

	va_start(ap, fmt);
	vsnprintf(str, sizeof(str), fmt, ap);
	va_end(ap);

	if (ctx.logLevel >= 10) {
		xprintf("%s", str);
		return;
	}

	curtick = msticks();
	maxtick = 0;

	acquireLock(&ctx.logLock);
	found = false;
	idx = ctx.logSize;
	for (i = 0; i < ctx.logSize;) {
		if (!found && !strcmp(ctx.log[i].message, str)) {
			found = true;
			ctx.log[i].numRepeats++;
		}
		delta = curtick - ctx.log[i].tick;
		if (maxtick < delta) {
			idx = i;
			maxtick = delta;
		}
		if (delta >= 1000 || ctx.log[i].numRepeats >= 1000) {
			if (ctx.log[i].numRepeats > 0)
				xprintf("%s (repeated %llu times)\n", ctx.log[i].message, ctx.log[i].numRepeats);
			ctx.log[i] = ctx.log[--ctx.logSize];
		} else {
			ctx.log[i].tick = curtick;
			i++;
		}
	}
	if (idx >= nelem(ctx.log))
		idx = 0;

	if (!found) {
		if (ctx.logSize < nelem(ctx.log))
			ctx.logSize++;
		else if (ctx.log[idx].numRepeats > 0)
			xprintf("%s (repeated %llu times)\n", ctx.log[idx].message, ctx.log[idx].numRepeats);

		snprintf(ctx.log[idx].message, sizeof(ctx.log[idx].message), "%s", str);
		ctx.log[idx].numRepeats = 0;
		ctx.log[idx].tick = curtick;
		xprintf("%s", str);
	}
	releaseLock(&ctx.logLock);
}
