#ifndef _NMPL_H_
#define _NMPL_H_

#include <stdint.h>

typedef struct Compress Compress;
typedef struct Compress_Vtable Compress_Vtable;

typedef void (*voidfn)(void);

typedef Compress *(*Compress_Constructor)(Compress *, unsigned char *, unsigned int);
typedef Compress *(*Compress_Decode)(Compress *, void *, int);
typedef Compress *(*Compress_Encode)(Compress *, const char *);
typedef Compress *(*Compress_IsSupported)(Compress *, void *);

struct Compress_Vtable {
	Compress_Constructor constructor;
	Compress_Decode decode;
	Compress_Encode encode;
	Compress_IsSupported is_supported;
};

struct Compress {
	uint32_t output_size;
	uint32_t output_type;
	uint8_t *output;
	uint32_t input_size;
	uint32_t input_type;
	uint8_t *input;
	uint8_t unk1[0x10000];
	Compress_Vtable vtable;
};

#endif
