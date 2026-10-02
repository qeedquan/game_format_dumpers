CFLAGS += -g3 -ggdb -Wall -Wextra -fPIC

ifeq ($(OS), Windows_NT)
	LDFLAGS += -limagehlp -ldbghelp -Wl,--export-all-symbols -Wl,--out-implib,steam_api.a
	OUTFILE := "steam_api.dll"
else
	UNAME := $(shell uname -s)
	OUTFILE := "libsteam_api.so"
	ifeq ($(UNAME), Linux)
		LDFLAGS += -ldl -shared -lpthread
	endif
endif

ifeq ($(BUILD_32), 1)
	CFLAGS += -m32
endif

ifeq ($(GAME), )
	GAME = DEFAULT
endif

include games.mk

DEFS += -D GAME="$(GAME)"

ifeq ($(OS), Windows_NT)
all:
	gcc -c *.c $(CFLAGS) $(DEFS)
	gcc -shared -o $(OUTFILE) *.o $(LDFLAGS)
else
all:
	gcc $(CFLAGS) -o $(OUTFILE) *.c $(LDFLAGS) $(DEFS)
endif

clean:
	rm -f *.a *.o *.so *.dll *.obj *.exp *.lib *.ilk *.pdb
