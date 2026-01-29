#include "philosophers.h"

long	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int sleep)
{
	long long	start;

	start = get_time();
	while (get_time() - start < sleep)
		usleep(1);
}
