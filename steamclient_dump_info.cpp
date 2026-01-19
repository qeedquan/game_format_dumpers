#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#if defined(_WIN32)
#include <windows.h>
#define loadlib(libname) LoadLibrary(libname)
#define getsym(handle, symbol) GetProcAddress(handle, symbol)
#else
#include <dlfcn.h>
#define loadlib(libname) dlopen(libname, RTLD_LAZY)
#define getsym(handle, symbol) dlsym(handle, symbol)
#endif

#include "steam_api.h"
#include "isteamappticket.h"

struct Version
{
	char client[64];
	char utils[64];
	char user[64];
	char appticket[64];
};

Version version = {
    "SteamClient014",
    "SteamUtils007",
    "SteamUser017",
    "STEAMAPPTICKET_INTERFACE_VERSION001",
};

S_API typedef ISteamClient *(S_CALLTYPE *CreateInterface)(const char *ver, bool *err);

[[noreturn]] void fatal(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	exit(1);
}

[[noreturn]] void usage()
{
	fprintf(stderr, "usage: library_file\n");
	exit(1);
}

void hexdump(uint8 *buf, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		printf("%02x ", buf[i]);
		if ((i & 15) == 0)
			printf("\n");
	}
	if ((len & 15) != 15)
		printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		usage();

	auto handle = loadlib(argv[1]);
	if (!handle)
		fatal("failed to load steam library");

	auto create_interface = (CreateInterface)getsym(handle, "CreateInterface");
	if (!create_interface)
		fatal("failed to load steam interface");

	bool err;
	auto steamclient = create_interface(version.client, &err);
	if (!steamclient || err)
		fatal("failed to create steam client");

	auto pipe = steamclient->CreateSteamPipe();
	auto user = steamclient->ConnectToGlobalUser(pipe);
	if (!pipe || !user)
		fatal("failed to create communication channel");

	auto steamutils = steamclient->GetISteamUtils(pipe, version.utils);
	if (!steamutils)
		fatal("failed to get steam utils");

	auto steamuser = steamclient->GetISteamUser(user, pipe, version.user);
	if (!steamuser)
		fatal("failed to get steam user");

	auto usersteamid = steamuser->GetSteamID();
	auto universe = steamutils->GetConnectedUniverse();
	auto appid = steamutils->GetAppID();

	auto steamappticket = (ISteamAppTicket *)steamclient->GetISteamGenericInterface(user, pipe, version.appticket);
	if (!steamappticket)
		fatal("failed to get app ticket");

	uint8 buf[1024] = {0};
	uint32 steamid, sig, nsig;
	auto nr = steamappticket->GetAppOwnershipTicketData(appid, buf, sizeof(buf), &appid, &steamid, &sig, &nsig);
	printf("universe %d user %d usersteamid %lld appid %d steamid %d sig %d nsig %d\n", universe, user, usersteamid.ConvertToUint64(), appid, steamid, sig, nsig);
	hexdump(buf, sizeof(buf));

	return 0;
}
