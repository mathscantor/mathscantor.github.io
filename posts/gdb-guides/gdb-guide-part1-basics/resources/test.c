#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void func_1(char *, size_t);
void func_2(char *, size_t);

void func_1(char *string, size_t size) {
    printf("String: %s\n", string);
    return;
}

void func_2(char *string, size_t size) {

    srand(time(NULL));
    int r_index = rand() % (size - 1);

    string[r_index] = '@';
    printf("String: %s\n", string);
    return;
}

int main(void) {

    char sample[] = "Hello World!";
    int choice = 0;
    while (1) {
        printf("Choice: ");
        scanf("%d", &choice);
        if (choice == 1) func_1(sample, sizeof(sample));
        else if (choice == 2) func_2(sample, sizeof(sample));
        else continue;
    }

    return 0;
}