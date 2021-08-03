#include "philo.h"

void	print_death(int id)
{
	struct timeval	tv;
	long long		ms;

	pthread_mutex_lock(&g_output);
	ms = ft_gettime();
	printf("%lld %d %s%s%s\n", ms, id, RED, "died", RESET);
	free_and_destroy_mutex();
	// pthread_mutex_unlock(&g_output);
}

int		check_times_eat(void)
{
	int		i;
	int		done;

	i = 0;
	done = 0;
	while (i < g_info.nb_of_philo)
	{
		if (g_state[i].times_eat == g_info.times_to_eat)
			done++;
		i++;
	}
	if (done == g_info.nb_of_philo)
	{
		pthread_mutex_lock(&g_output);
		free_and_destroy_mutex();
		return (1);
	}
	return (0);
}

int		monitor_philo_death(void)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < g_info.nb_of_philo)
		{
			if (g_state[i].eating == 0 &&
				ft_gettime() - g_state[i].last_time_eat > g_info.time_to_die)
			{
				print_death(g_state[i].id);
				return (0);
			}
			i++;
		}
		if (check_times_eat() == 1)
			return (0);
	}
	return (0);
}