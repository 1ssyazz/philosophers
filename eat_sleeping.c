/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleeping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:23:37 by msukri            #+#    #+#             */
/*   Updated: 2022/08/11 16:47:45 by msukri           ###   ########.fr       */
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
		if (ft_dying(value))
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
		if (ft_dead(thread))
			return (ft_death(value, i + 1));
		if (ft_dying(value))
			return (0);
		usleep(100);
	}
	return (1);
}

int	ft_forks(t_value *value, int i)
{
	pthread_mutex_lock(&(value->mutex[(i + 1) % value->philo]));
	pthread_mutex_lock(&(value->mutex[(i)]));
	if (value->lock[i] == i && value->lock[(i + 1) % value->philo] == i)
	{
		pthread_mutex_unlock(&(value->mutex[(i + 1) % value->philo]));
		pthread_mutex_unlock(&(value->mutex[(i)]));
		return (1);
	}
	pthread_mutex_unlock(&(value->mutex[(i + 1) % value->philo]));
	pthread_mutex_unlock(&(value->mutex[(i)]));
	return (0);
}

int	ft_forks1(t_value *value, int i)
{
	pthread_mutex_lock(&(value->mutex[(i)]));
	pthread_mutex_lock(&(value->mutex[(i + 1) % value->philo]));
	if (value->lock[i] == i && value->lock[(i + 1) % value->philo] == i)
	{
		pthread_mutex_unlock(&(value->mutex[(i)]));
		pthread_mutex_unlock(&(value->mutex[(i + 1) % value->philo]));
		return (1);
	}
	pthread_mutex_unlock(&(value->mutex[(i)]));
	pthread_mutex_unlock(&(value->mutex[(i + 1) % value->philo]));
	return (0);
}
