/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:53:46 by msukri            #+#    #+#             */
/*   Updated: 2022/08/02 21:03:43 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_create(t_value *value);

int	ft_create_join(t_value *value)
{
	int	ret;

	ret = ft_create(value);
	return (ret);
}

static int	ft_create(t_value *value)
{
	int			i;

	i = -1;
	if (value->eat_freq)
		pthread_create(&value->full, NULL, ft_full, (void *)value);
	while (++i < value->philo)
	{
		value->p[i]->philo_pid = fork();
		value->p[i]->last_meal = timer();
		if (value->p[i]->philo_pid == 0)
		{
			if (pthread_create(&value->p[i]->thread, NULL,
					monitor_die, (void *)value->p[i]) != 0)
			{
				ft_output_err(-3);
				return (0);
			}
			routine(value->p[i]);
			exit(1);
		}
		usleep(100);
	}
	ft_close_process(value);
	return (1);
}

void	ft_close_process(t_value *value)
{
	int	i;
	int	status;

	i = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) || WIFSIGNALED(status))
	{
		while (i < value->philo)
			kill(value->p[i++]->philo_pid, SIGKILL);
	}
}
