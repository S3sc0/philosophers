#include "../headers/philo.h"

void	free_and_destroy_mutex(void)
{
	int		i;
	t_all	all;

	all = global_function(NULL);
	i = 0;
	while (i < all.info.nb_of_philo)
	{
		pthread_mutex_destroy(&all.fork[i]);
		i++;
	}
	free(all.fork);
	free(all.state);
}

void	philosopher(t_state *state)
{
	int		left;
	int		right;
	t_all	all;

	all = global_function(NULL);
	left = state->id - 1;
	right = (left + 1) % all.info.nb_of_philo;
	pthread_mutex_lock(&all.fork[left]);
	print_state(state->id, "has taken a fork", BLUE);
	pthread_mutex_lock(&all.fork[right]);
	print_state(state->id, "has taken a fork", BLUE);
	print_state(state->id, "is eating", YELLOW);
	state->eating = 1;
	state->times_eat++;
	state->last_time_eat = ft_gettime();
	mysleep(all.info.time_to_eat);
	state->eating = 0;
	pthread_mutex_unlock(&all.fork[right]);
	pthread_mutex_unlock(&all.fork[left]);
	print_state(state->id, "is sleeping", PURPLE);
	mysleep(all.info.time_to_sleep);
	print_state(state->id, "is thinking", GREEN);
}

void	*looping(void *arg)
{
	t_state		*state;
	int			i;
	t_all		all;

	all = global_function(NULL);
	state = (t_state *)arg;
	i = 0;
	if (all.info.times_to_eat == 0)
		while (1)
			philosopher(state);
	else
	{
		while (i < all.info.times_to_eat)
		{
			philosopher(state);
			i++;
		}
	}
	return (NULL);
}

int	create_philosophers(void)
{
	int			i;
	pthread_t	*th;
	t_all		all;

	all = global_function(NULL);
	i = 0;
	th = malloc(sizeof(pthread_t) * all.info.nb_of_philo);
	while (i < all.info.nb_of_philo)
	{
		if (pthread_create(&th[i], NULL, looping, (void *)&all.state[i]))
			return (error_m("error: can't create thread"));
		usleep(100);
		i++;
	}
	free(th);
	global_function(&all);
	return (0);
}

int	main(int ac, char *av[])
{
	if (parse_info(ac, av) == 1 || initialize_mutex() == 1)
		return (1);
	initialize_state();
	if (create_philosophers() == 1)
		return (1);
	return (monitor_philo_death());
}
