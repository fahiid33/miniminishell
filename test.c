#include <stdio.h>

int check_for_EOF() {
    if (feof(stdin)) return 1;
    int c = getc(stdin);
    if (c == EOF) return 1;
    ungetc(c, stdin);
    printf("dick\n");
}

int main() {
    printf("Start typing:\n");
    while (!check_for_EOF()) {
        int bytes_typed = 0;
        while (getchar() != '\n') bytes_typed++;
        printf("You typed a line of %d bytes\n", bytes_typed);
    }
}