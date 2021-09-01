#include "philo.h"

t_all	global_function(t_all *fill)
{
	static t_all	var;

	if (fill)
		var = *fill;
	return (var);
}
