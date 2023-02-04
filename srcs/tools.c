#include "../headers/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;
	int	large;

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

int	error_m(char *message)
{
	printf("%s%s%s\n", RED, message, RESET);
	return (1);
}

long long	ft_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_state(int id, char *status, char *color)
{
	t_all	all;

	all = global_function(NULL);
	pthread_mutex_lock(&all.output);
	printf("%lld %d %s%s%s\n", ft_gettime(), id, color, status, RESET);
	pthread_mutex_unlock(&all.output);
}

void	mysleep(int ms)
{
	struct timeval	tv;
	long long		current;
	long long		last;

	gettimeofday(&tv, NULL);
	last = tv.tv_usec + (tv.tv_sec * 1000000);
	current = last;
	usleep((ms - 10) * 1000);
	while ((current - last) < (ms * 1000))
	{
		gettimeofday(&tv, NULL);
		current = tv.tv_usec + (tv.tv_sec * 1000000);
	}
}
