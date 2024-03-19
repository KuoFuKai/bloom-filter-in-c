#include "hash.h"

unsigned int djb2(const void *_str)
{
    const char *str = (const char *)_str;
    unsigned int hash = 5381;
    char c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

unsigned int jenkins(const void *_str)
{
    const char *key = (const char *)_str;
    unsigned int hash = 0;
    while (*key) {
        hash += *key;
        hash += (hash << 10);
        hash ^= (hash >> 6);
        key++;
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

unsigned int sdbm(const void *_str)
{
    const char *str = (const char *)_str;
    unsigned int hash = 0;
    char c;
    while ((c = *str++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

unsigned int fnv1a(const void *_str) {
    const char *str = (const char *)_str;
    unsigned int hash = 0x811C9DC5;
    while (*str) {
        hash ^= (unsigned char)(*str++);
        hash *= 0x01000193;
    }
    return hash;
}

unsigned int multiplication_hash(const void *_str) {
    const char *str = (const char *)_str;
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 33) ^ (*str++);
    }
    return hash;
}

unsigned int rs_hash(const void *_str) {
    const char *str = (const char *)_str;
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    while (*str) {
        hash = hash * a + (*str++);
        a = a * b;
    }
    return hash;
}

unsigned int pjw_hash(const void *_str) {
    const char *str = (const char *)_str;
    unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;

    while (*str) {
        hash = (hash << OneEighth) + (*str++);
        if ((test = hash & HighBits) != 0) {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
    return hash;
}

unsigned int elf_hash(const void *_str) {
    const char *str = (const char *)_str;
    unsigned int hash = 0;
    unsigned int x = 0;

    while (*str) {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }
    return hash;
}

unsigned int bkdr_hash(const void *_str) {
    const char *str = (const char *)_str;
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return hash;
}

unsigned int dek_hash(const void *_str) {
    const char *str = (const char *)_str;
    unsigned int hash = (unsigned int)strlen(str);

    while (*str) {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str++);
    }

    return hash;
}

unsigned int ap_hash(const void *_str) {
    const char *str = (const char *)_str;
    unsigned int hash = 0xAAAAAAAA;

    for (size_t i = 0; *str; ++i) {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str++) ^ (hash >> 3)) :
                                (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
    }

    return hash;
}