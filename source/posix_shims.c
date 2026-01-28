#include <errno.h>

int access(const char *path, int mode) {
    (void)path;
    (void)mode;
    errno = ENOSYS;
    return -1;
}
