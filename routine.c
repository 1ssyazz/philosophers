/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:49:22 by msukri            #+#    #+#             */
/*   Updated: 2022/08/11 16:25:45 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *thread)
{
	t_value	*value;
	int		i;
	int		eat_frequency;

	value = ((t_thread *)thread)->value;
	i = ((t_thread *)thread)->philo_index;
	eat_frequency = value->eat_freq;
	while (eat_frequency--)
	{
		if (!ft_wait_fork(thread, value, i))
			break ;
		if (!ft_eating(thread, value, i))
			break ;
		if (!ft_unlock_forks(value, i))
			break ;
		if (!ft_sleeping(thread, value, i))
			break ;
		ft_output(value, i, THINKING);
		usleep(1000);
	}
	ft_output(value, i, FULL);
	free(thread);
	return (NULL);
}

void	ft_output(t_value *value, int i, char *message)
{
	pthread_mutex_lock(&value->dead_mutex);
	if (!(ft_dying(value)))
	{
		if (!ft_strncmp(message, FORK_TAKEN, 8))
		{
			printf(GRN"%li "CYN"%d ", timer(), i + 1);
			printf(WHI"has taken a "YEL"fork"NC"\n");
		}
		else if (!ft_strncmp(message, EATING, 8))
		{
			printf(GRN"%li "CYN"%d ", timer(), i + 1);
			printf(WHI"is "YEL"eating"NC"\n");
		}
		else
			ft_output_1(i, message);
	}
	pthread_mutex_unlock(&value->dead_mutex);
}

void	ft_output_1(int i, char *message)
{
	if (!ft_strncmp(message, SLEEPING, 8))
	{
		printf(GRN"%li "CYN"%d ", timer(), i + 1);
		printf(WHI"is "YEL"sleeping"NC"\n");
	}
	if (!ft_strncmp(message, THINKING, 8))
	{
		printf(GRN"%li "CYN"%d ", timer(), i + 1);
		printf(WHI"is "YEL"thinking"NC"\n");
	}
	if (!ft_strncmp(message, FULL, 8))
	{
		printf(GRN"%li "CYN"%d ", timer(), i + 1);
		printf(WHI"is "GRN"full"NC"\n");
	}
}
