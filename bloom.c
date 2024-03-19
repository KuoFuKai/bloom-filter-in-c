#include "bloom.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

BloomFilter* BloomFilter_Create(unsigned size) {
    BloomFilter* bf = malloc(sizeof(BloomFilter));
    bf->size = size;
    bf->table = calloc(size, sizeof(unsigned char));
    bf->item_count = 0;
    bf->hash_count = 0;
    bf->head = NULL;
    return bf;
}

void BloomFilter_AddHash(BloomFilter* bf, hash_function f) {
    hash_node *h = (hash_node *)malloc(sizeof(hash_node));
    if (h == NULL) {
        return;
    }
    
    h->func = f;
    h->next = NULL;
    bf->hash_count++;
    
    if (bf->head == NULL) {
        bf->head = h;
    } else {
        hash_node *last = bf->head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = h;
    }
}

void BloomFilter_AddElement(BloomFilter* bf, void *data) {
    hash_node *h = bf->head;
    bf->item_count++;
    while (h) {
        unsigned hash = h->func(data);
        hash %= bf->size;
        bf->table[hash >> 3] |= 0x80 >> (hash & 7);
        h = h->next;
    }
}

double BloomFilter_FalsePositiveRate(BloomFilter* bf) {
    double p = (-1.0 * bf->hash_count * bf->item_count) / bf->size;
    return pow(1 - exp(p), (double)bf->hash_count);
}

unsigned BloomFilter_ItemCount(BloomFilter* bf) {
    return bf->item_count;
}

unsigned BloomFilter_HashCount(BloomFilter* bf) {
    return bf->hash_count;
}

void BloomFilter_Destroy(BloomFilter* bf) {
    while (bf->head) {
        hash_node *p = bf->head;
        bf->head = bf->head->next;
        free(p);
    }
    free(bf->table);
    free(bf);
}