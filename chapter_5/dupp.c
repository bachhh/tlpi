#define _LARGEFILE64_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include <errno.h>

int
main( int argc, char *argv[])
{

    exit(EXIT_SUCCESS);
}

int
dupp(int oldfd)
{
    if ( fcntl(oldfd, F_GETFL) < 0){
        errno = EBADF;
        return -1;
    }
    return fcntl(oldfd, F_DUPFD, 0);
}

int
dupp2(int oldfd, int newfd )
{
    if ( fcntl(oldfd, F_GETFL) < 0){
        errno = EBADF;
        return -1;
    }
    if(oldfd == newfd){
        return newfd;
    }
    int ret = fcntl(newfd, F_GETFD);
    if (ret < 0 && errno != EBADF){
        return -1;
    } else if (ret >= 0){
        close(newfd);
    }
    return fcntl(oldfd, F_DUPFD, newfd);
}

int
checkFD(int fd1, int fd2)
{
    int flag1 = fcntl(fd1, F_GETFL);
    int flag2 = fcntl(fd2, F_GETFL);
    if (flag1 != flag2)
        return -1;
    off_t off1 = lseek(fd1, 0, SEEK_CUR);
    off_t off2 = lseek(fd2, 0, SEEK_CUR);
    if (off1 != off2)
        return -1;

    return 0;

}
