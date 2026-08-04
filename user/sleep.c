#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    int n;

    if (argc != 2) {
        printf("Usage: sleep n\n");
        exit(1);
    }
    n = atoi(argv[1]);
    pause(n);
    exit(0);
}
