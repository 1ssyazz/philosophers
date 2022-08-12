/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:11:44 by msukri            #+#    #+#             */
/*   Updated: 2022/08/11 16:48:59 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_one_philo(void *thread, t_value *value, int i);
static void	ft_takefork_rightleft(t_value *value, int i);
static void	ft_takefork_leftright(t_value *value, int i);

int	ft_wait_fork(void *thread, t_value *value, int i)
{
	if (value->philo == 1)
		return (ft_one_philo(thread, value, i));
	while (!(ft_dying(value)))
	{
		if (i % 2)
			ft_takefork_rightleft(value, i);
		else
			ft_takefork_leftright(value, i);
		if (ft_dead(thread))
			return (ft_death(value, i));
		if (i % 2)
		{
			if (ft_forks(value, i))
				return (!(ft_dying(value)));
		}
		else
		{
			if (ft_forks1(value, i))
				return (!(ft_dying(value)));
		}
		usleep(100);
	}
	return (0);
}

static int	ft_one_philo(void *thread, t_value *value, int i)
{
	while (1)
	{
		if (value->lock[i] == -1)
		{
			value->lock[i] = i;
			ft_output(value, i, "My fork!");
		}
		if (ft_dead(thread))
			return (ft_death(value, i));
		usleep(100);
	}
}

static void	ft_takefork_rightleft(t_value *value, int i)
{
	pthread_mutex_lock(&(value->mutex[(i + 1) % value->philo]));
	pthread_mutex_lock(&(value->mutex[i]));
	if (value->lock[(i + 1) % value->philo] == -1
		&& value->lock[i] == -1)
	{
		value->lock[(i + 1) % value->philo] = i;
		value->lock[i] = i;
		ft_output(value, i, FORK_TAKEN);
		ft_output(value, i, FORK_TAKEN);
	}
	pthread_mutex_unlock(&(value->mutex[(i + 1) % value->philo]));
	pthread_mutex_unlock(&(value->mutex[i]));
}

static void	ft_takefork_leftright(t_value *value, int i)
{
	pthread_mutex_lock(&(value->mutex[(i)]));
	pthread_mutex_lock(&(value->mutex[(i + 1) % value->philo]));
	if (value->lock[i] == -1
		&& value->lock[(i + 1) % value->philo] == -1)
	{
		value->lock[i] = i;
		value->lock[(i + 1) % value->philo] = i;
		ft_output(value, i, FORK_TAKEN);
		ft_output(value, i, FORK_TAKEN);
	}
	pthread_mutex_unlock(&(value->mutex[i]));
	pthread_mutex_unlock(&(value->mutex[(i + 1) % value->philo]));
}

int	ft_unlock_forks(t_value *value, int i)
{
	if (i % 2)
	{
		pthread_mutex_lock(&(value->mutex[(i + 1) % value->philo]));
		pthread_mutex_lock(&(value->mutex[i]));
	}
	else
	{
		pthread_mutex_lock(&(value->mutex[(i)]));
		pthread_mutex_lock(&(value->mutex[(i + 1) % value->philo]));
	}
	value->lock[i] = -1;
	value->lock[(i + 1) % value->philo] = -1;
	if (i % 2)
	{
		pthread_mutex_unlock(&(value->mutex[(i + 1) % value->philo]));
		pthread_mutex_unlock(&(value->mutex[i]));
	}
	else
	{
		pthread_mutex_unlock(&(value->mutex[i]));
		pthread_mutex_unlock(&(value->mutex[(i + 1) % value->philo]));
	}
	if (ft_dying(value))
		return (0);
	return (1);
}
