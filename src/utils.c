#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "ft_clib.h"

uint64_t get_random_uint64() {
    uint64_t ret;
    int devrandom = open("/dev/urandom", O_RDONLY);
    if (devrandom == -1) {
        ERROR("opening /dev/random failed. errno is %s", errno_name(errno));
        // TODO: exit gracefully
        return 0;
    }
    if (read(devrandom, &ret, sizeof(uint64_t)) != sizeof(uint64_t)) {
        close(devrandom);
        ERROR("failed reading 8 random bytes. errno is %s", errno_name(errno));
        // TODO: exit gracefully
        return 0;
    }
    close(devrandom);
    return ret;
}
