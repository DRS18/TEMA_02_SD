#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"

int main() {
    struct Hashtable *ht;
    int hmax = 0, final = 0;
    FILE *words;
    char temp_word[100][100], aux[100], *p;

    words = fopen("words.txt", "wt");
    while (scanf("%s", aux) == 1) {
        strcat(aux, "\n");
        // printf("%s", temp_word);
        fprintf(words, aux);
        hmax++;
    }
    fclose(words);

    ht = malloc(sizeof(struct Hashtable));
    init_ht(ht, hmax, hash_function_string, compare_function_strings);

    words = fopen("words.txt", "rt");
    fseek(words, 0, SEEK_END);
    final = ftell(words);
    fseek(words, 0, SEEK_SET);

    int cnt = 0;

    while (ftell(words) < final) {
        fgets(temp_word[cnt], 100, words);
        p = temp_word[cnt];
        p[strlen(p) - 1] = '\0';
        // printf("\nIl pun pe %s\n", temp_word[cnt]);
        put(ht, temp_word[cnt], strlen(temp_word[cnt]) + 1, temp_word[cnt]);
        // print_ht(ht);
        ++cnt;
    }
    print_ht(ht);

    fclose(words);
    free_ht(ht);
}