/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:11:44 by msukri            #+#    #+#             */
/*   Updated: 2022/08/02 16:11:41 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait_fork(t_philo *philo)
{
	sem_wait(philo->value->sem_fork);
	ft_output(philo->value, philo->philo_index, FORK_TAKEN);
	sem_wait(philo->value->sem_fork);
	ft_output(philo->value, philo->philo_index, FORK_TAKEN);
	ft_output(philo->value, philo->philo_index, EATING);
	sem_wait(philo->sem_eat);
	sem_post(philo->value->sem_meal);
	philo->last_meal = timer();
	while ((timer() - philo->last_meal < philo->value->time_to_eat))
		usleep(100);
	sem_post(philo->sem_eat);
}

void	ft_unlock_forks(t_philo *philo)
{
	sem_post(philo->value->sem_fork);
	sem_post(philo->value->sem_fork);
}
