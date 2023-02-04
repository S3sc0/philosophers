#include "../headers/philo.h"

int	check_for_mistakes(int ac, char *av[])
{
	int		i;
	int		j;

	i = 1;
	if (ac < 5 || ac > 6)
		return (error_m("error: wrong number of arguments"));
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (av[i][j] < '0' || av[i][j] > '9' || av[i][0] == '0')
				return (error_m("error: unvalid argument"));
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_info(int ac, char *av[])
{
	t_all	all;

	all.info.since_started = 0;
	if (check_for_mistakes(ac, av) == 1)
		return (1);
	all.info.since_started = ft_gettime();
	all.info.nb_of_philo = ft_atoi(av[1]);
	all.info.time_to_die = ft_atoi(av[2]);
	all.info.time_to_eat = ft_atoi(av[3]);
	all.info.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		all.info.times_to_eat = ft_atoi(av[5]);
	else
		all.info.times_to_eat = 0;
	global_function(&all);
	return (0);
}

int	initialize_mutex(void)
{
	int		i;
	t_all	all;

	all = global_function(NULL);
	i = 0;
	all.fork = malloc(sizeof(pthread_mutex_t) * all.info.nb_of_philo);
	while (i < all.info.nb_of_philo)
	{
		if (pthread_mutex_init(&all.fork[i], NULL) != 0)
			return (error_m("error: can't initialzie mutex"));
		i++;
	}
	if (pthread_mutex_init(&all.output, NULL) != 0)
		return (error_m("error: can't initialzie mutex"));
	global_function(&all);
	return (0);
}

void	initialize_state(void)
{
	int		i;
	t_all	all;

	all = global_function(NULL);
	i = 0;
	all.state = malloc(sizeof(t_state) * all.info.nb_of_philo);
	while (i < all.info.nb_of_philo)
	{
		all.state[i].id = i + 1;
		all.state[i].eating = 0;
		all.state[i].last_time_eat = ft_gettime();
		all.state[i].times_eat = 0;
		i++;
	}
	global_function(&all);
}
