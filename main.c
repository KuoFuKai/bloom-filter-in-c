#include "bloom.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    BloomFilter* bloom = BloomFilter_Create(1024);
    BloomFilter_AddHash(bloom, djb2);
    BloomFilter_AddHash(bloom, jenkins);
    BloomFilter_AddHash(bloom, sdbm);
    BloomFilter_AddHash(bloom, fnv1a);
    BloomFilter_AddHash(bloom, multiplication_hash);
    BloomFilter_AddHash(bloom, rs_hash);
    BloomFilter_AddHash(bloom, pjw_hash);
    BloomFilter_AddHash(bloom, elf_hash);
    BloomFilter_AddHash(bloom, bkdr_hash);
    BloomFilter_AddHash(bloom, dek_hash);
    BloomFilter_AddHash(bloom, ap_hash);
    
    int random_int;
    int element_size = 100;
    for(int i = 0; i < element_size; i++) {
        random_int = rand();
        BloomFilter_AddElement(bloom, &random_int);
        // printf("%d\n", random_number); 
    }

    printf("The bloom filter contains %u items.\n", BloomFilter_ItemCount(bloom));
    printf("False positive rate: %f%%\n", BloomFilter_FalsePositiveRate(bloom) * 100);
    
    BloomFilter_Destroy(bloom);
    return 0;
}
