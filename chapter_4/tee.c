#include <ctype.h>
#include <fcntl.h>

#include "tlpi_hdr.h"

#ifndef BUF_SIZE        /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif

int
main(int argc, char *argv[])
{
    int outputFD, openFlags;
    mode_t filePerms;

    int opt;
    Boolean appndFILE = FALSE;

    if (argc > 3  || argc < 1 || strcmp(argv[1], "--help") == 0)
        usageErr("%s old-file new-file [-a append to file]\n", argv[0]);

    while((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
        case 'a': appndFILE = TRUE; break;
        case '?': usageErr("%s Unrecognized option -%c\n", argv[0], optopt); break;

        default: fatal("Unexpected case in switch");
        }
    }

    // set permission for output file
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;      /* rw-rw-rw- */

    openFlags = O_CREAT | O_WRONLY;

    if ( appndFILE ){
        openFlags |= O_APPEND;
    } else {
        openFlags |= O_TRUNC;
    }

    outputFD = open(argv[optind], openFlags, filePerms);

    ssize_t numRead;
    char buf[BUF_SIZE + 1];

    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0 ){
        if (write(outputFD, buf, numRead) != numRead)
            fatal("couldn't write whole buffer to file");
        if(write(STDOUT_FILENO, buf, numRead) != numRead)
            fatal("couldn't write whole buffer to stdout");
    }

    if (numRead == -1)
        errExit("readFailed");
    if (close(outputFD) == -1)
        errExit("close output");

    exit(EXIT_SUCCESS);
}

