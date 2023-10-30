#include <time.h>
#include <internal/syscall.h>
#include <errno.h>

/* https://www.daemon-systems.org/man/nanosleep.2.html */

int nanosleep(const struct timespec *rqtp, struct timespec *rmtp) {

    int ret = syscall(__NR_nanosleep, rqtp, rmtp);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
}
