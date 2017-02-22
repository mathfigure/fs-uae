/*
* Redpill for UAE - The Un*x Amiga Emulator
*
* (c) mathfigure <mathfigure@gmail.com>
*/

#include "uae/redpill.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define BLUE	"\x1b[1;34m"
#define GREEN	"\x1b[1;32m"
#define RED	"\x1b[1;31m"
#define NOCOLOR	"\x1b[0m"

void redpill_quit(const char *msg)
{
    printf(RED "FAIL.\n" NOCOLOR);
    perror(msg);
    exit(EXIT_FAILURE);
}

void* shm_new(int size, const char *sid)
{
    printf(">Allocating shared memory: " BLUE "%s" NOCOLOR " = %d bytes, ",sid,size);
    int fd = shm_open(sid, O_CREAT|O_RDWR, S_IRUSR | S_IWUSR);
    if(fd == -1)
        redpill_quit("shm_open() failed!");
    ftruncate(fd, size);
    void *ptr = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED) {
        close(fd);
        redpill_quit("mmap() failed!");
    }
    close(fd);
    printf(GREEN "OK\n" NOCOLOR);
    return ptr;
}
