#include <ctype.h>
#include <fcntl.h>

#include "tlpi_hdr.h"

#ifndef BUF_SIZE        /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif

#define printable(ch) (isprint((unsigned char) ch) ? ch : '#')

int
main(int argc, char *argv[])
{
    int inputFD, outputFD, openFlags;
    mode_t filePerms;

    int opt;
    Boolean appndFILE = FALSE;

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s old-file new-file [-a append to file]\n", argv[0]);


    while((opt = getopt(argc, argv, ":a")) != -1) {
        switch (opt) {
        case 'a': appndFILE = TRUE; break;
        case '?': usageErr("%s Unrecognized option -%c\n", argv[0], optopt); break;

        default: fatal("Unexpected case in switch");
        }
    }

    inputFD = open(argv[1], O_RDONLY);
    if (inputFD == -1)
        errExit("opening file %s\n", argv[1]);

    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;      /* rw-rw-rw- */
    openFlags = O_WRONLY;

    if (appndFILE ){
        openFlags |= O_APPEND;
    } else {
        openFlags |= O_TRUNC;
    }
    outputFD = open(argv[2], openFlags, filePerms);

    exit(EXIT_SUCCESS);
}

