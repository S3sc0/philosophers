#include "../headers/philo.h"

void	print_death(int id)
{
	long long		ms;
	t_all			all;

	all = global_function(NULL);
	pthread_mutex_lock(&all.output);
	global_function(&all);
	ms = ft_gettime();
	printf("%lld %d %s%s%s\n", ms, id, RED, "died", RESET);
	free_and_destroy_mutex();
}

int	monitor_philo_death(void)
{
	int		i;
	int		done;
	t_all	all;

	all = global_function(NULL);
	while (1)
	{
		i = -1;
		done = 0;
		while (++i < all.info.nb_of_philo)
		{
			if (all.state[i].eating == 0 && ft_gettime()
				- all.state[i].last_time_eat > all.info.time_to_die)
			{
				print_death(all.state[i].id);
				return (0);
			}
			if (all.info.times_to_eat != 0 && all.state[i].times_eat
				== all.info.times_to_eat)
				done++;
		}
		if (done == all.info.nb_of_philo)
			return (0);
	}
	return (0);
}
