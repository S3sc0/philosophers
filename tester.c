#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int	main(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	printf("Hello let's wait for 3sec ...! - %ld\n", time.tv_sec);
	usleep((1000 * 3) * 1000);
	gettimeofday(&time, NULL);
	printf("You're finished waiting! - %ld\n", time.tv_sec);
	return (0);
}