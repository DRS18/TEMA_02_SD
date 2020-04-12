#ifndef __HASHTABLE_H
#define __HASHTABLE_H

struct info {
    void *key;
    void *value;
    unsigned char freq;
};

struct Hashtable {
    struct info **buckets; // Array de struct info 
    int size; // Nr. total de vectori ocupati
    int hmax; // Nr. bucket-uri
    // (Pointer la) Functie pentru a calcula valoarea hash asociata cheilor.
    unsigned int (*hash_function)(void*);
    // (Pointer la) Functie pentru a compara doua chei.
    int (*compare_function)(void*, void*);
};

void init_ht(struct Hashtable *ht, int hmax, unsigned int (*hash_function)(void*), int (*compare_function)(void*, void*));

void put(struct Hashtable *ht, void *key, int key_size_bytes, void *value);

void print_ht(struct Hashtable *ht);

void free_ht(struct Hashtable *ht);

// Functii de comparare a cheilor
int compare_function_ints(void *a, void *b);

int compare_function_strings(void *a, void *b);

// Functii de hashing
unsigned int hash_function_int(void *a);

unsigned int hash_function_string(void *a);


#endif