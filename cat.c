#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]);

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    int in_fd, rd_count;
    char buffer[BUF_SIZE];

    if (argc != 2) exit(1);

    /* Read File */
    in_fd = open(argv[1], O_RDONLY);
    if (in_fd < 0) exit(2);

    /* While loop to print file content */
    while(read(in_fd, buffer, BUF_SIZE) > 0)
    {
        printf("%s", buffer);
    }

    /* Close the file */
    close(in_fd);
    if (rd_count == 0)
        exit(0);
    else
        exit(5);
}