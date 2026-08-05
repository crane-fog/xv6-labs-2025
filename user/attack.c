#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

#define DATASIZE (8 * 4096)

int main(int argc, char* argv[])
{
    // Your code here.
    char* data = sbrk(DATASIZE);
    if (data[29] == '.') {
        printf("%s\n", data + 32);
        return 0;
    }
    else {
        return 1;
    }
}
