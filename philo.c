/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzouar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 11:35:56 by aamzouar          #+#    #+#             */
/*   Updated: 2021/06/14 11:35:57 by aamzouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		valid_number(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int		check_arg_errors(int ac, char *av[])
{
	int		i;

	if (ac < 5 || ac > 6)
		return (printf("Error: wrong number of arguments\n") * 0 + 1);
	i = 1;
	while (i < ac)
	{
		if (valid_number(av[i]))
			return (printf("Error: argument [%d] isn't valid\n", i) * 0 + 1);
		i++;
	}
	return (0);
}

void	parse_the_data(int ac, char *av[])
{
	g_philo_attr.nb_of_philo = ft_atoi(av[1]);
	g_philo_attr.time_to_die = ft_atoi(av[2]);
	g_philo_attr.time_to_eat = ft_atoi(av[3]);
	g_philo_attr.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		g_philo_attr.times_to_eat = ft_atoi(av[5]);
}

void	*philosopher(void *arg)
{
	printf("i'm philosopher number [%d]\n", *(int *)arg);
	free(arg);
	return NULL;
}

int		create_philosophers(void)
{
	int			i;
	pthread_t	th[g_philo_attr.nb_of_philo];
	int			*nb;

	i = 0;
	while (i < g_philo_attr.nb_of_philo)
	{
		nb = malloc(sizeof(int));
		*nb = i;
		if (pthread_create(&th[i], NULL, &philosopher, nb))
			return (printf("Error: can't create the thread [%d]\n", i) * 0 + 1);
		i++;
	}
	i = 0;
	while (i < g_philo_attr.nb_of_philo)
	{
		if (pthread_join(th[i], NULL))
			return (printf("Error: can't join the thread [%d]\n", i) * 0 + 1);
		i++;
	}
	return (0);
}

int     main(int ac, char *av[])
{
	if (check_arg_errors(ac, av))
		return (1);
	parse_the_data(ac, av);
	if (create_philosophers())
		return (1);
	return (0);
}