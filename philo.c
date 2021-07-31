#include "philo.h"

int		ft_atoi(const char *str)
{
	int i;
	int sign;
	int nb;
	int large;

	large = 0;
	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && ++large)
		nb = nb * 10 + str[i++] - 48;
	if (large > 10 && sign == -1)
		return (1);
	if (large > 10 && sign == 1)
		return (-1);
	return (nb * sign);
}

int		error_m(char *message)
{
	printf("%s%s%s\n", RED, message, RESET);
	return (1);
}

long long	ft_gettime(void)
{
	long long		ret;
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	ret = tv.tv_sec * 1000;
	ret = ret + tv.tv_usec / 1000;
	return (ret);
}

void	print_state(int id, char *status, char *color)
{
	struct timeval	tv;
	long long		ms;

	pthread_mutex_lock(&g_output);
	ms = ft_gettime();
	printf("%lld %d %s%s%s\n", ms, id, color, status, RESET);
	pthread_mutex_unlock(&g_output);
}

void	mysleep(int ms)
{
	struct timeval	tv;
	long long		current;
	long long		last;

	gettimeofday(&tv, NULL);
	last = tv.tv_usec + (tv.tv_sec * 1000000);
	usleep((ms - 50) * 1000);
	while ((current - last) < (ms * 1000))
	{
		gettimeofday(&tv, NULL);
		current = tv.tv_usec + (tv.tv_sec * 1000000);
	}
}

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
	g_th = malloc(sizeof(pthread_t) * g_info.nb_of_philo);
	while (i < g_info.nb_of_philo)
	{
		g_state[i].id = i + 1;
		g_state[i].eating = 0;
		g_state[i].sleeping = 0;
		g_state[i].last_time_eat = 0;
		g_state[i].current_eat_time = 0;
		g_state[i].times_eat = 0;
		i++;
	}
}

void	philosopher(t_state state)
{
	int		left;
	int		right;

	left = state.id - 1;
	right = (left + 1) % g_info.nb_of_philo;
	pthread_mutex_lock(&g_fork[left]);
	print_state(state.id, "has taken a fork 1", BLUE);
	pthread_mutex_lock(&g_fork[right]);
	print_state(state.id, "has taken a fork 2", BLUE);
	state.eating = 1;
	state.current_eat_time = ft_gettime();
	state.times_eat++;
	print_state(state.id, "is eating", YELLOW);
	mysleep(g_info.time_to_eat);
	state.eating = 0;
	state.last_time_eat = state.current_eat_time;
	pthread_mutex_unlock(&g_fork[right]);
	pthread_mutex_unlock(&g_fork[left]);
	print_state(state.id, "is sleeping", PURPLE);
	mysleep(g_info.time_to_sleep);
}

void	*looping(void *arg)
{
	t_state		state;
	int			i;

	state = *(t_state*)arg;
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
	int		i;

	i = 0;
	while (i < g_info.nb_of_philo)
	{
		if (pthread_create(&g_th[i], NULL, looping, (void*)&g_state[i]))
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
	for (int i = 0; i < g_info.nb_of_philo; i++)
	{
		if (pthread_join(g_th[i], NULL))
			return (error_m("error: can't join thread"));
	}
	return (0);
}