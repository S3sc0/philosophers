#include "philo.h"

void	print_death(int id)
{
	long long		ms;

	pthread_mutex_lock(&g_output);
	ms = ft_gettime();
	printf("%lld %d %s%s%s\n", ms, id, RED, "died", RESET);
	free_and_destroy_mutex();
}

int		monitor_philo_death(void)
{
	int		i;
	int		done;

	while (1)
	{
		i = 0;
		done = 0;
		while (i < g_info.nb_of_philo)
		{
			if (g_state[i].eating == 0 &&
				ft_gettime() - g_state[i].last_time_eat > g_info.time_to_die)
			{
				print_death(g_state[i].id);
				return (0);
			}
			if (g_info.times_to_eat != 0 &&
				g_state[i].times_eat == g_info.times_to_eat)
				done++;
			i++;
		}
		if (done == g_info.nb_of_philo)
			return (0);
	}
	return (0);
}