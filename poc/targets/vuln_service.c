#include <stdio.h>
#include <stdlib.h>

void debug_shell(void) {
    system("/bin/sh");
}

void log_message(char *msg) {
    printf(msg);
}

int main(void) {
    char buf[64];

    puts("=== MiniLog v1.0 ===");

    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        log_message(buf);
    }
    
    return 0;
}