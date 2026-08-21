#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc < 2){
        printf("usage: tail file [n]\n");
        exit(1);
    }

    int n;
    if(argc == 3)
        n = atoi(argv[2]);
    else
        n = 10;

    int fd = open(argv[1], O_RDONLY);
    if(fd < 0){
        printf("tail: cannot open %s\n", argv[1]);
        exit(1);
    }

    int bytes;
    char ch;
    int lines = 0;


    while((bytes = read(fd, &ch, 1)) > 0){
        if(ch == '\n')
            lines++;
    }

    close(fd);

    fd = open(argv[1], O_RDONLY);
    if(fd < 0){
        printf("tail: cannot reopen file\n");
        exit(1);
    }

    int start_line = lines - n + 1;
    if(start_line < 1)
        start_line = 1;

    int current_line = 1;


    while((bytes = read(fd, &ch, 1)) > 0){
        if(current_line >= start_line)
            write(1, &ch, 1);

        if(ch == '\n')
            current_line++;
    }

    close(fd);
    exit(0);
}
