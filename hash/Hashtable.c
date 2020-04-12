#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"

// Functii de comparare a cheilor
int compare_function_ints(void *a, void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b) {
        return 0;
    } else if (int_a < int_b) {
        return -1;
    } else {
        return 1;
    }
}

int compare_function_strings(void *a, void *b) {
    char *str_a = (char *)a;
    char *str_b = (char *)b;

    return strcmp(str_a, str_b);
}

// Functii de hashing
unsigned int hash_function_int(void *a) {
    /*
     * Credits: https://stackoverflow.com/a/12996028/7883884
     */
    unsigned int uint_a = *((unsigned int *)a);

    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = (uint_a >> 16u) ^ uint_a;
    return uint_a;
}

unsigned int hash_function_string(void *a) {
    /*
     * Credits: http://www.cse.yorku.ca/~oz/hash.html
     */
    unsigned char *puchar_a = (unsigned char*) a;
    unsigned long hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

    return hash;
}

// Functie apelata dupa alocarea unui hashtable pentru a-l initializa.
void init_ht(struct Hashtable *ht, int hmax, unsigned int (*hash_function)(void*), int (*compare_function)(void*, void*)) {
    ht->buckets = malloc(sizeof(struct info *) * hmax);
    if (ht->buckets == NULL) {
        return;
    }
    for (int i = 0; i < hmax; i++) {
        ht->buckets[i] = calloc(1, sizeof(struct info));

        // strcpy((char*)ht->buckets[i]->value, "\0");
        // memcpy(ht->buckets[i]->key, "\0", 1);
    }
    ht->hmax = hmax;
    ht->hash_function = hash_function;
    ht->compare_function = compare_function;
}

void free_ht(struct Hashtable *ht) {
    int i = 0;
    int hmax = ht->hmax;
    for (i = 0; i < hmax; i++) {
        // if (ht->buckets[i] != NULL) {
            free(ht->buckets[i]->key);
            free(ht->buckets[i]);
        // }
    }
    free(ht->buckets);
    free(ht);
}

void put(struct Hashtable *ht, void *key, int key_size_bytes, void *value) {
    int h = 0;
    struct info *curr_info;
    
    curr_info = calloc(1, sizeof(struct info));
    curr_info->key = calloc(1, key_size_bytes);
    memcpy(curr_info->key, key, key_size_bytes);
    curr_info->value = value;

    h = ht->hash_function(key) % ht->hmax;
    // printf("%d\n", h);

    if (ht->buckets[h]->freq == 0) {
        // printf("DAAA\n");
        // memcpy(ht->buckets[h], curr_info, sizeof(struct info));
        free(ht->buckets[h]); // AICI FREE
        ht->buckets[h] = curr_info;
        // printf("%p - %p\n", (void *)ht->buckets[h], (void *)curr_info);
        // free(curr_info->key);
        // free(curr_info);
        ht->buckets[h]->freq++;
        return;
    } else {
        while (ht->buckets[h]->freq != 0) {
            if (strcmp(ht->buckets[h]->value, curr_info->value) == 0) {
                ht->buckets[h]->freq++;
                free(curr_info->key);
                free(curr_info);
                // printf("ACELASI CUV %p - %p\n", (void *)ht->buckets[h], (void *)curr_info);
                return;
            } else if (ht->buckets[h + 1]->freq == 0) {
                free(ht->buckets[h+1]); // AICI FREE
                ht->buckets[h + 1] = curr_info;
                ht->buckets[h + 1]->freq++;
                // printf("%p - %p\n", (void *)ht->buckets[h + 1], (void *)curr_info);
                return;
            }   

            if (h < ht->hmax - 1) {
                h++;
            } else {
                h = 0;
            }
        }
    }
}

void print_ht(struct Hashtable *ht) {
    for (int i = 0; i < ht->hmax; i++) {
        if (ht->buckets[i]->value != NULL) {
            printf("%s %d\n", (char*)ht->buckets[i]->value, ht->buckets[i]->freq);
        }
    }
}