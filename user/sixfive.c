#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

const char* SEPS = " -\r\t\n./,";

void sixfive(int fd)
{
    char cur = '\0';
    int num = 0;
    int status = 0; // 0: 正常, 1: 异常

    while (1) {
        int n = read(fd, &cur, 1);
        if (n < 0) {
            printf("sixfive: read error\n");
            exit(1);
        }
        else if (n == 0) {
            if (num % 6 == 0 || num % 5 == 0) {
                printf("%d\n", num);
            }
            break;
        }
        else if (strchr(SEPS, cur) == 0) {
            // 不是分隔符
            if (status == 0) {
                if (cur >= '0' && cur <= '9') {
                    num = num * 10 + (cur - '0');
                }
                else {
                    status = 1;
                }
            }
        }
        else {
            // 是分隔符
            if (status == 0) {
                if (num % 6 == 0 || num % 5 == 0) {
                    printf("%d\n", num);
                }
                num = 0;
            }
            else {
                status = 0;
                num = 0;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: sixfive <filename>\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            printf("sixfive: cannot open %s\n", argv[i]);
            exit(1);
        }
        sixfive(fd);
        close(fd);
    }

    exit(0);
}
