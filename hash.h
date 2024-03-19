#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <stddef.h>

unsigned int djb2(const void *_str);
unsigned int jenkins(const void *_str);
unsigned int sdbm(const void *_str);
unsigned int fnv1a(const void *_str);
unsigned int multiplication_hash(const void *_str);
unsigned int rs_hash(const void *_str);
unsigned int pjw_hash(const void *_str);
unsigned int elf_hash(const void *_str);
unsigned int bkdr_hash(const void *_str);
unsigned int dek_hash(const void *_str);
unsigned int ap_hash(const void *_str);

#endif