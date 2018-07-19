
## 5.3 Open file status flag

The O_APPEND flag specify that all write to file will happends at one past the
end of file byte, (file offset will always be at EOF before writting, even
when using lseek() )

***Function pwrite(4) according POSIX supposed to not be affected by O_APPEND FLAG
when writting, however on Linux implementation pwrite() append to EOF
regardless of input's offset.***

## 5.5 Duplicating File Descriptors

When specify joining stderr and stdout, the shell achieve this by duplicating
stdout file descriptors. Note that the kernel avoid opening a the
stdout twice, since that would make the stdout offset un-synced between
the 2 file descriptors.



