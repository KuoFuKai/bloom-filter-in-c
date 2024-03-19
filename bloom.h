#ifndef BLOOM_H
#define BLOOM_H

#include <stdbool.h>

typedef unsigned int (*hash_function)(const void *data);

typedef struct hash_node {
    hash_function func;
    struct hash_node* next;
} hash_node;

typedef struct {
    unsigned char *table;
    unsigned size, hash_count, item_count;
    hash_node *head;
} BloomFilter;

BloomFilter* BloomFilter_Create(unsigned size);
void BloomFilter_AddHash(BloomFilter* bf, hash_function f);
void BloomFilter_AddElement(BloomFilter* bf, void *data);
void BloomFilter_Destroy(BloomFilter* bf);
double BloomFilter_FalsePositiveRate(BloomFilter* bf);
unsigned BloomFilter_ItemCount(BloomFilter* bf);
unsigned BloomFilter_HashCount(BloomFilter* bf);

#endif