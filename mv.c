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

    if (argc != 4) exit(1);

    /* First Option */
    /*
        If the source file and the destination are 
        in different location from the current directory
    */
    if (strcmp(argv[1], "1") == 0)
    {
        in_fd = open(argv[2], O_RDONLY);
        
        if (in_fd < 0) exit(9);
        
        char temp_filename[PATH_MAX] = ""; // temporary file name

        for(i = strlen(argv[2]) - 1; i >= 0; i--)
        {
            if (strchr(&(argv[2][i]), '/') != NULL)
            {
                strcat(temp_filename, &(argv[2][i]));
                break;
            }
        }

        if (strcmp(&(argv[3][strlen(argv[3])-1]), "/") == 0)
        {
            argv[3][strlen(argv[3])-1] = "\0";
            strcat(argv[3], temp_filename);
        }
        else if (strcmp(&(argv[3][strlen(argv[3])-1]), "/") != 0)
        {
            strcat(argv[3], temp_filename);
        }

        // Create output file
        out_fd = creat(argv[3], OUTPUT_MODE);
        if (out_fd < 0) exit(10);
    }

    /* Second Option */
    /*
        If source file is the file from current directory
    */
    else if (strcmp(argv[1], "2") == 0)
    {
        in_fd = open(argv[2], O_RDONLY);
        
        if (in_fd < 0) exit(2);

        if (strcmp(&(argv[3][strlen(argv[3])-1]), "/") == 0)
        {
            argv[3] = strcat(argv[3], argv[2]);
        }
        else if (strcmp(&(argv[3][strlen(argv[3])-1]), "/") != 0){
            argv[3] = strcat(argv[3], "/");
            argv[3] = strcat(argv[3], argv[2]);
        }

        out_fd = creat(argv[3], OUTPUT_MODE);
        if (out_fd < 0) exit(3);
    }

    /* Third Option */
    /*
        Rename file from current directory
    */
    else if (strcmp(argv[1], "3"), == 0)
    {
        in_fd = open(argv[2], O_RDONLY);
        if (in_fd < 0) exit(4)

        out_fd = creat(argv[3], OUTPUT_MODE);
        if (out_fd < 0) exit(5)
    }

    else {
        exit(6);
    }

    while(TRUE)
    {
        rd_count = read(in_fd, buffer, BUF_SIZE);
        if (rd_count <= 0) break;
        // Write buffer to output file
        wt_count = write(out_fd, buffer, rd_count);
        if (wt_count <= 0) exit(7)
    }

    // Close the file
    close(in_fd);
    close(out_fd);

    remove(argv[2]); // For cp command, just comment this line

    if(rd_count == 0) exit(0);
    else exit(8);
}