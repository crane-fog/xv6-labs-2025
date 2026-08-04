#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"

char* fmtname(char* path)
{
    char* p;
    // Find first character after last slash.
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    return p + 1;
}

void find(char* path, char* filename, char* cmd[MAXARG])
{
    char newpath[512];
    struct stat st;
    struct dirent de;
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        printf("find: cannot open %s\n", path);
        exit(1);
    }
    if (fstat(fd, &st) < 0) {
        printf("find: cannot stat %s\n", path);
        close(fd);
        exit(1);
    }
    switch (st.type) {
        case T_FILE:
            if (strcmp(fmtname(path), filename) == 0) {
                if (cmd[0] != 0) {
                    int pid = fork();
                    if (pid < 0) {
                        printf("find: fork error\n");
                        exit(1);
                    }
                    else if (pid == 0) {
                        int i = 0;
                        while (cmd[i] != 0) {
                            i++;
                        }
                        cmd[i] = path;
                        exec(cmd[0], cmd);
                        printf("find: exec error\n");
                        exit(1);
                    }
                    else {
                        wait(0);
                    }
                }
                else {
                    printf("%s\n", path);
                }
            }
            break;
        case T_DIR:
            if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(newpath)) {
                printf("find: path too long\n");
                break;
            }
            while (read(fd, &de, sizeof(de)) == sizeof(de)) {
                if (de.inum == 0) {
                    continue;
                }
                if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
                    continue;
                }
                strcpy(newpath, path);
                strcpy(newpath + strlen(path), "/");
                strcpy(newpath + strlen(path) + 1, de.name);
                find(newpath, filename, cmd);
            }
            break;
        default:
            break;
    }
    close(fd);
}

int main(int argc, char* argv[])
{
    if (argc < 3 || (argc > 3 && strcmp(argv[3], "-exec") != 0)) {
        printf("Usage: find <directory> <filename> (-exec <cmd>)\n");
        exit(1);
    }
    char* cmd[MAXARG] = {0};
    if (argc > 3) {
        for (int i = 4; i < argc; i++) {
            cmd[i - 4] = argv[i];
        }
    }
    find(argv[1], argv[2], cmd);
    exit(0);
}
