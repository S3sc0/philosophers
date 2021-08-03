#include "philo.h"

int		check_for_mistakes(int ac, char *av[])
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

int		parse_info(int ac, char *av[])
{
	if (check_for_mistakes(ac, av) == 1)
		return (1);
	g_info.nb_of_philo = ft_atoi(av[1]);
	g_info.time_to_die = ft_atoi(av[2]);
	g_info.time_to_eat = ft_atoi(av[3]);
	g_info.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		g_info.times_to_eat = ft_atoi(av[5]);
	else
		g_info.times_to_eat = 0;
	return (0);
}

int		initialize_mutex(void)
{
	int		i;

	i = 0;
	g_fork = malloc(sizeof(pthread_mutex_t) * g_info.nb_of_philo);
	while (i < g_info.nb_of_philo)
	{
		if (pthread_mutex_init(&g_fork[i], NULL) != 0)
			return (error_m("error: can't initialzie mutex"));
		i++;
	}
	if (pthread_mutex_init(&g_output, NULL) != 0)
		return (error_m("error: can't initialzie mutex"));
	return (0);
}

void	initialize_state(void)
{
	int		i;

	i = 0;
	g_state = malloc(sizeof(t_state) * g_info.nb_of_philo);
	while (i < g_info.nb_of_philo)
	{
		g_state[i].id = i + 1;
		g_state[i].eating = 0;
		g_state[i].last_time_eat = ft_gettime();
		g_state[i].times_eat = 0;
		i++;
	}
}