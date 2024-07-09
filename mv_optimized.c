#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int main(int argc, char *argv[]);

#define BUF_SIZE 4096
#define OUTPUT_MODE 0700
#define TRUE 1

int main(int argc, char *argv[])
{
    int in_fd, out_fd, rd_count, wt_count;
    char buffer[BUF_SIZE];
    int i;

    if (argc != 3) exit(1);

    // Open source file
    in_fd = open(argv[1], O_RDONLY);

    if (in_fd < 0) exit(1);

    // Construct variable for destination
    char dest_filename[PATH_MAX] = "";
    strcpy(dest_filename, argv[2]);

    // Check if destination is directory
    if (dest_filename[strlen(dest_filename) - 1] == "/")
    {
        char *filename = strrchr(argv[1], "/");
        if (filename)
        {
            strcat(dest_filename, filename + 1);
        }
        else {
            strcat(dest_filename, argv[1]);
        }
    }

    // Create output file
    out_fd = creat(dest_filename, OUTPUT_MODE);
    if (out_fd < 0) exit(2);

    // Copy content from source to destination
    while(TRUE)
    {
        rd_count = read(in_fd, buffer, BUF_SIZE);
        if (rd_count <= 0) break;
        // Write buffer to output file
        wt_count = write(out_fd, buffer, rd_count);
        if (wt_count <= 0) exit(3)
    }

    // Close the file
    close(in_fd);
    close(out_fd);

    remove(argv[1]); // For cp command, just comment this line

    if(rd_count == 0) exit(0);
    else exit(4);
}