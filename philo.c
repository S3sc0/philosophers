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
				return (error_m("error: unvalid number"));
			j++;
		}
		i++;
	}
	return (0);
}

int		parse_info(int ac, char *av[], t_info *info)
{
	if (check_for_mistakes(ac, av) == 1)
		return (1);
	info->nb_of_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->times_to_eat = ft_atoi(av[5]);
	return (0);
}

int		main(int ac, char *av[])
{
	t_info	info;
	t_state	*state;

	if (parse_info(ac, av, &info) == 1)
		return (1);
	return (0);
}