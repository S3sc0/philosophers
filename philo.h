#ifndef PHILO_H
#define PHILO_H

#define RED " \033[0;31m"
#define RESET "\033[0m"
#define BLUE "\033[0;34m"
#define	YELLOW "\033[0;33m"
#define PURPLE "\033[0;35m"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

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
	int				id;
	int				eating;
	int				sleeping;
	int				last_time_eat;
	int				current_eat_time;
	int				times_eat;
}				t_state;

pthread_mutex_t		*g_fork;
pthread_mutex_t		g_output;
t_info				g_info;
t_state				*g_state;
pthread_t			*g_th;

#endif