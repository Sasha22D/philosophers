#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

__uint64_t	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_usec);
}

int	main()
{
	__uint64_t now;
	__uint64_t start;

	start = get_time();
	usleep(20000);
	now = get_time();
	printf("%ld\n", now - start);
}