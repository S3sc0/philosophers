#include "philo.h"

void	free_and_destroy_mutex(void)
{
	int		i;

	i = 0;
	while (i < g_info.nb_of_philo)
	{
		pthread_mutex_destroy(&g_fork[i]);
		i++;
	}
	free(g_fork);
	free(g_state);
}

void	philosopher(t_state *state)
{
	int		left;
	int		right;

	left = state->id - 1;
	right = (left + 1) % g_info.nb_of_philo;
	pthread_mutex_lock(&g_fork[left]);
	print_state(state->id, "has taken a fork", BLUE);
	pthread_mutex_lock(&g_fork[right]);
	print_state(state->id, "has taken a fork", BLUE);
	print_state(state->id, "is eating", YELLOW);
	state->eating = 1;
	state->times_eat++;
	state->last_time_eat = ft_gettime();
	mysleep(g_info.time_to_eat);
	state->eating = 0;
	pthread_mutex_unlock(&g_fork[right]);
	pthread_mutex_unlock(&g_fork[left]);
	print_state(state->id, "is sleeping", PURPLE);
	mysleep(g_info.time_to_sleep);
	print_state(state->id, "is thinking", GREEN);
}

void	*looping(void *arg)
{
	t_state		*state;
	int			i;

	state = (t_state*)arg;
	i = 0;
	if (g_info.times_to_eat == 0)
		while (1)
			philosopher(state);
	else
		while (i < g_info.times_to_eat)
		{
			philosopher(state);
			i++;
		}
	return (NULL);
}

int		create_philosophers(void)
{
	int			i;
	pthread_t	th;

	i = 0;
	while (i < g_info.nb_of_philo)
	{
		if (pthread_create(&th, NULL, looping, (void*)&g_state[i]))
			return (error_m("error: can't create thread"));
		usleep(100);
		i++;
	}
	return (0);
}

int		main(int ac, char *av[])
{
	if (parse_info(ac, av) == 1 || initialize_mutex() == 1)
		return (1);
	initialize_state();
	if (create_philosophers() == 1)
		return (1);
	return (monitor_philo_death());
}