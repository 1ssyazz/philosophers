/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:49:22 by msukri            #+#    #+#             */
/*   Updated: 2022/08/02 20:58:51 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_full(void *value)
{
	t_value	*val;
	int		eat_freq;
	int		i;

	val = (t_value *)value;
	eat_freq = 0;
	while (eat_freq < val->eat_freq)
	{
		i = 0;
		while (i <= val->philo)
		{
			sem_wait(val->sem_meal);
			i++;
		}
		eat_freq++;
	}
	i = 0;
	while (i < val->philo)
		ft_output(val, val->p[i++]->philo_index, FULL);
	sem_wait(val->sem_print);
	i = 0;
	while (i < val->philo)
		kill(val->p[i++]->philo_pid, SIGKILL);
	return (0);
}

void	*routine(t_philo *philo)
{
	while (1)
	{
		ft_wait_fork(philo);
		ft_unlock_forks(philo);
		ft_sleeping(philo);
		ft_output(philo->value, philo->philo_index, THINKING);
		usleep(100);
	}
	return (NULL);
}

void	*monitor_die(void *philo)
{
	t_philo	*p;

	p = ((t_philo *)philo);
	while (1)
	{
		sem_wait(p->sem_eat);
		if (timer() - p->last_meal >= p->value->time_to_die)
		{
			ft_output(p->value, p->philo_index, DIED);
			exit(1);
		}
		sem_post(p->sem_eat);
		usleep(100);
	}
	return (0);
}

void	ft_output(t_value *value, int i, char *message)
{
	sem_wait(value->sem_print);
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
	if (message[0] != 'D')
		sem_post(value->sem_print);
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
	if (!ft_strncmp(message, DIED, 8))
	{
		printf(GRN"%li "CYN"%d ", timer(), i + 1);
		printf(RED"died""\n");
	}
}
