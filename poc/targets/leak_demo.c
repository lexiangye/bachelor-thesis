#include <stdio.h>

int main(void) {
    long local_secret = 0x1337;

    char buf[64];

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 1;
    }

    printf(buf);

    return 0;
}
