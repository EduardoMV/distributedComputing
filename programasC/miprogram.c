#include <stdio.h>

int main(int argc, char *argv[]) {

    printf("You wrote %d parameter(s). They are:\n", argc - 1);

    for (int i = 1; i < argc; i++) {
        printf("%d.- %s\n", i, argv[i]);
    }

    return 0;
}
