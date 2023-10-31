#include <time.h>
#include <internal/syscall.h>
#include <errno.h>

/* https://www.daemon-systems.org/man/nanosleep.2.html */

int nanosleep(const struct timespec *requested_time, struct timespec *remaining) {

    int ret = syscall(__NR_nanosleep, requested_time, remaining);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
}

unsigned int sleep(unsigned int seconds) {
    /* https://man7.org/linux/man-pages/man3/sleep.3.html */

    struct timespec requested_time;
    requested_time.tv_sec = seconds;
    requested_time.tv_nsec = 0;

    // using nanosleep to implement sleep
    int ret = nanosleep(&requested_time, &requested_time);
    
    if (ret < 0) {
		errno = -ret;
		return -1;
	} else {
        return requested_time.tv_sec;
    }

    return 0;
}
