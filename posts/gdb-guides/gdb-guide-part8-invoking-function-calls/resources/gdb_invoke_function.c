#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint16_t id;
    char name[256];
    uint8_t is_deceased;
} person_t;

void do_nothing() {
    printf("Do nothing!\n");
}

void hello(const char *name) {
    printf("Hello, %s!\n", name);
}

int add(int a, int b) {
    return a + b;
}

char *get_person_name(person_t *person) {
    return person->name;
}

int main() {
    printf("Program started. Waiting in main...\n");
    getchar();  // Pause to give you time to attach with GDB
    printf("Exiting main.\n");
    return 0;
}
