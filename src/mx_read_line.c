#include "libmx.h"

int mx_read_line(char** lineptr, size_t buf_size, char delim, const int fd) {
    if (buf_size == 0 || fd == 0) {
        return -2;
    }

    (*lineptr) = (char*)mx_realloc(*lineptr, buf_size);
    mx_memset((*lineptr), '\0', malloc_size((*lineptr)));
    size_t ress = 0;
    char buf;

    if (read(fd, &buf, 1)) {
        if (buf == delim) {
            return ress;
        }

        (*lineptr) = (char*)mx_realloc(*lineptr, ress + 1);
        (*lineptr)[ress] = buf;
        ress++;
    }
    else {
        return -1;
    }

    while (read(fd, &buf, 1)) {
        if (buf == delim) {
            break;
        }

        if (ress >= buf_size) {
            (*lineptr) = (char*)mx_realloc(*lineptr, ress + 1);
        }

        (*lineptr)[ress] = buf;
        ress++;
    }

    (*lineptr) = (char*)mx_realloc(*lineptr, ress + 1);

    size_t free_ress = malloc_size((*lineptr)) - ress;
    mx_memset(&(*lineptr)[ress], '\0', free_ress);

    return ress + 1;
}

