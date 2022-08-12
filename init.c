/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:52:26 by msukri            #+#    #+#             */
/*   Updated: 2022/08/11 16:37:41 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_value(t_value *value)
{
	value->philo = 0;
	value->time_to_die = 0;
	value->time_to_eat = 0;
	value->time_to_sleep = 0;
	value->dying_philo = 0;
	value->eat_freq = -1;
}

int	ft_value_setup(t_value *value, int argc, char **argv)
{
	value->philo = ft_atoi(argv[1]);
	value->time_to_die = ft_atoi(argv[2]);
	value->time_to_eat = ft_atoi(argv[3]);
	value->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		value->eat_freq = ft_atoi(argv[5]);
	value->thread = malloc(sizeof(pthread_t) * (value->philo));
	if (!(value->thread))
		return (0);
	value->mutex = malloc(sizeof(pthread_mutex_t) * (value->philo));
	if (!(value->mutex))
		return (0);
	value->lock = malloc(sizeof(int) * (value->philo));
	if ((!value->lock))
		return (0);
	if (ft_mutex_init(value) == 0)
		return (0);
	return (1);
}

int	ft_mutex_init(t_value *value)
{
	int	i;

	i = -1;
	while (++i < value->philo)
	{
		if (pthread_mutex_init(&(value->mutex[i]), NULL) != 0)
			return (0);
		value->lock[i] = -1;
	}
	if (pthread_mutex_init(&(value->dying), NULL) != 0)
		return (0);
	return (!(pthread_mutex_init(&(value->dead_mutex), NULL) != 0));
}

t_thread	*ft_thread_handler(t_value *value, int i)
{
	t_thread	*thread;

	thread = malloc(sizeof(t_thread));
	if (!thread)
		return (NULL);
	thread->value = value;
	thread->philo_index = i;
	thread->last_meal = 0;
	return (thread);
}

long	timer(void)
{
	struct timeval		time;
	static time_t		start_sec = 0;
	static suseconds_t	start_micro_sec = 0;

	gettimeofday(&time, NULL);
	if (!start_sec)
	{
		start_sec = time.tv_sec;
		start_micro_sec = time.tv_usec;
	}
	return (((time.tv_sec - start_sec) * 1000)
		+ (time.tv_usec - start_micro_sec) / 1000);
}
