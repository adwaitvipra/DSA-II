#ifndef MEMALLOC_H
#define MEMALLOC_H

#include <stdint-gcc.h>
#include <stddef.h>
#define METABLOCK_SIZE sizeof(metaDataBlock)
#define TRUE 1
#define FALSE 0
#define NUMBER_OF_BINS_PER_PAGE SYS_PG_SZ / (BIN_SZ + METABLOCK_SIZE)

typedef struct metaDataBlock
{
    int isFree;
    uint32_t blockSize;
    struct metaDataBlock *prevBlock;
    struct metaDataBlock *nextBlock;
    struct metaDataBlock *headPtr;
} metaDataBlock;

typedef metaDataBlock *mdb;

int isPageEmpty(mdb);
void *getPages(int);
void freePages(void *, int);
mdb getFreePages(mdb);
void FREE(void *);
void *MALLOC(size_t);
void *CALLOC(size_t, size_t);
void *REALLOC(void *, size_t);

extern size_t SYS_PG_SZ;

#endif