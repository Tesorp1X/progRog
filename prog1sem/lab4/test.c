#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define CHUNK_SIZE 16
/*
char *readWord(FILE *in) {
    int allocated = 0;
    int used = 1;
    char *word = NULL;
    char c;
    while (c = fgetc(in) != EOF) {
        if (c == ' ') break;
        if (allocated <= used) {
            char *temp_word = realloc(word, sizeof(char) * (allocated + CHUNK_SIZE));
            if (!temp_word) {
                printf("ERROR : Allocation failed");
                break;
            }
            word = temp_word; allocated += CHUNK_SIZE;
        }
        word[used - 1] = c; used++;
    }
    if (word) word[used - 1] = 0;

    return word;
}
*/

int main() {
    FILE *in = fopen("input.txt", "r");
    char word1[] = "a";
    char word2[] = "b";
    printf("%d\n", (strcmp(word1, word2)));

    return 0;
}