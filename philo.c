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

void	check_arg_errors(int ac, char *av[])
{
	int		i;

	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
	i = 1;
	while (i < ac)
	{
		if (valid_number(av[i]))
		{
			printf("Error: argument number [%d] isn't a valid number\n", i);
			exit(1);
		}
		i++;
	}
}

int     main(int ac, char *av[])
{
	check_arg_errors(ac, av);
	return (0);
}