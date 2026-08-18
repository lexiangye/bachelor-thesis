#include <stdio.h>

long global_secret = 0;

int main(void) {
    char buf[64];

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 1;
    }

    printf(buf);

    printf("global_secret = 0x%x\n", global_secret);

    return 0;
}
