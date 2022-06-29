#include "../inc/philosophers.h"

long timestamp(void)
{
	struct timeval time;
	long i;

	gettimeofday(&time, NULL);
	i = ((int)time.tv_sec * 1000) + ((int)time.tv_usec / 1000);
	return (i);
}

time_t time_diff(time_t past, time_t present)
{
	return (present - past);
}