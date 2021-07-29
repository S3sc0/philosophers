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

int		parse_info(int ac, char *av[])
{
	
}

int		main(int ac, char *av[])
{
	if (parse_info(ac, av) == 1)
		return (1);
	return (0);
}