CC=cc
CXX=c++
WINECC=winegcc
CFLAGS=-Wall -pedantic -ggdb -g3

SRC=nmpl.c ioutil.c

all:
	$(CC) $(CFLAGS) -o nmpl.exe $(SRC)

wine:
	$(WINECC) $(CFLAGS) -o nmpl.exe $(SRC)

clean:
	rm -f *.exe *.so
