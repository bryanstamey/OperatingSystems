#include <stdio.h>  /* printf(), fopen() */
#include <stdlib.h> /* exit(), EXIT_FAILURE */
#include <fcntl.h>  /* open() */
#include <unistd.h> /* ssize_t, size_t, read() */
#include <errno.h>

#define BUF_SIZE 4096

int main(int argc, char* argv[]) {

    int srcFD, destFD;  /* return values of open() */
    mode_t dest_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    char *buf[BUF_SIZE];
    ssize_t bytes_read;

    if (argc != 3) {
       printf("\nUsage: copy source_file destination_file\n");
       exit(EXIT_FAILURE);
    }

    /* Open source file and verify */
    srcFD = open(argv[1], O_RDONLY);

    if(srcFD == -1) {
        printf("\nErr: source file %s could not be opened\nerrno = %d\n", argv[1], errno);
        exit(EXIT_FAILURE);
    }

    /* Create destination file and verify */
    destFD = creat(argv[2], dest_mode);

    if(destFD == -1) {
        printf("\nErr: destination file %s could not be opened\nerrno = %d\n", argv[2], errno);
        exit(EXIT_FAILURE);
    }

    /* Perform copy */
    while((bytes_read = read(srcFD, buf, BUF_SIZE)) > 0) {
        write(destFD, buf, bytes_read);
    }

    if (bytes_read == -1)
        printf("\nErr: could not write to %s", argv[1]);

    close(srcFD);
    close(destFD);
    exit(EXIT_SUCCESS);
}