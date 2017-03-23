#ifndef __ALI_H__
#define __ALI_H__
#include <stdint.h>
#include <stddef.h>
#define ALI_BLOCK_SIZE 16

typedef uint8_t data_t;

typedef struct {
data_t * data;
size_t size;
size_t max_size;
} alint;

void ali_free (alint *);
alint * alint_init (size_t);
#endif
