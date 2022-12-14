/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:00:25 by msukri            #+#    #+#             */
/*   Updated: 2022/08/11 16:24:37 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_dead(void *thread)
{
	t_value	*value;
	long	last_meal;

	value = ((t_thread *)thread)->value;
	last_meal = ((t_thread *)thread)->last_meal;
	if (timer() - last_meal > value->time_to_die)
	{
		return (1);
	}
	return (0);
}

int	ft_death(t_value *value, int i)
{
	pthread_mutex_lock(&value->dead_mutex);
	if (ft_dying(value))
	{
		pthread_mutex_unlock(&value->dead_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_lock(&value->dying);
		value->dying_philo = 1;
		pthread_mutex_unlock(&value->dying);
		printf(GRN"%li "CYN"%d ", timer(), i + 1);
		printf(RED"died"NC"\n");
		pthread_mutex_unlock(&value->dead_mutex);
	}
	return (0);
}

int	ft_dying(t_value *value)
{
	pthread_mutex_lock(&value->dying);
	if (value->dying_philo)
	{
		pthread_mutex_unlock(&value->dying);
		return (1);
	}
	pthread_mutex_unlock(&value->dying);
	return (0);
}
