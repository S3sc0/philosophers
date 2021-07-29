#ifndef PHILO_H
#define PHILO_H

#define RED " \033[0;31m"
#define RESET "\033[0m"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

typedef struct	s_info
{
	int		nb_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_to_eat;
}				t_info;

typedef struct	s_state
{
	t_info			*data;
	int				id;
	int				eating;
	int				sleeping;
	int				last_time_eat;
	int				current_eat_time;
	int				times_eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*output;
}				t_state;

#endif