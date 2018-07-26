# 13.5 Advising I/O patterns to kernel

POSIX define a template method for advising the kernel of a program's data
access patterns:
    int posxi_fadvis(int fd, off_t offset, off_t len, int advice);
where advice can be any of the consts:
    POSIX_FADV_NORMAL
    POSIX_FADV_SEQUENTIAL
    POSIX_FADV_RANDOM
    POSIX_FADV_WILLNED
    POSIX_FADV_DONTNEED
    POSIX_FADV_NOREUSE

The linux kernel implement this method since kernel 2.6 onwards

# 13.6 Direct I/O

From Kernel 2.4, Linux allows processes to bypass buffer cache on disk I/O
when open file with flag O_DIRECT.

The main concern here is that there is no way to ensure data integrity on disk
between a file descriptor opended with O_DIRECT in one process and without in
another process.

Also decrease performance greatly since the kernel can provide optimizations
on the buffer cache before performing disk write data.


