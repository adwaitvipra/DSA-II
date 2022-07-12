#ifndef MALLOC_H
#define MALLOC_H


#include <stdint.h>
#include <stddef.h>

void*  MALLOC(size_t );

void*  CALLOC(size_t ,size_t );

void* REALLOC(void* , size_t );

void  FREE(void *);


#endif