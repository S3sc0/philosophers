#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int				s = 0;
pthread_mutex_t	mutex;


void	*routine()
{
	pthread_mutex_lock(&mutex);
	int		*res = malloc(sizeof(int));
	for (int i = 0; i < 10000000; i++)
	{
		s++;
	}
	*res = s;
	pthread_mutex_unlock(&mutex);
	return (res);
}

int     main(void)
{
	pthread_t	th[4];
	int			*res;	

	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 4; i++)
	{
		pthread_create(th + i, NULL, &routine, NULL);
	}
	for (int i = 0; i < 4; i++)
	{
		pthread_join(th[i], (void **) &res);
		printf("our value stored in variable [res] is: %d\n", *res);
		free(res);
	}
	printf("our value stored in variable [s] is: %d\n", s);
	pthread_mutex_destroy(&mutex);
	return (0);
}