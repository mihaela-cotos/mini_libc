#ifndef __TIME_H__
#define __TIME_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>

struct timespec {
	uint64_t	tv_sec;
	long		tv_nsec;
};

int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);

#ifdef __cplusplus
}
#endif

#endif