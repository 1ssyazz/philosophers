/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleeping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:23:37 by msukri            #+#    #+#             */
/*   Updated: 2022/07/31 15:59:25 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eating(void *thread, t_value *value, int i)
{
	long	time_start;

	time_start = timer();
	((t_thread *)thread)->last_meal = time_start;
	ft_output(value, i, EATING);
	while (timer() - time_start < value->time_to_eat)
	{
		if (ft_dead(thread))
			return (ft_death(value, i));
		if (value->dying_philo)
			return (0);
		usleep(100);
	}
	return (1);
}

int	ft_sleeping(void *thread, t_value *value, int i)
{
	long	time_start;

	time_start = timer();
	ft_output(value, i, SLEEPING);
	while (timer() - time_start < value->time_to_sleep)
	{
		if (value->dying_philo || ft_dead(thread))
			return (ft_death(value, i + 1));
		usleep(100);
	}
	return (1);
}
