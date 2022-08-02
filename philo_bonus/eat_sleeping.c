/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleeping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:23:37 by msukri            #+#    #+#             */
/*   Updated: 2022/08/02 14:39:58 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleeping(t_philo *philo)
{
	long	time_start;

	time_start = timer();
	ft_output(philo->value, philo->philo_index, SLEEPING);
	while (timer() - time_start < philo->value->time_to_sleep)
		usleep(100);
}
