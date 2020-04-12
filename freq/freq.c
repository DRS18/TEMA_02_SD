#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    int n;
    unsigned char freq[2000001];

    for (int i = 0; i < 2000001; i++) {
        freq[i] = 0;
    }

    while (scanf("%d", &n) == 1) {
        freq[n]++;
    }

    for (int i = 0; i < 2000001; i++) {
        if (freq[i] != 0) {
            printf("%d %d\n", i, freq[i]);
        }
    }
}
