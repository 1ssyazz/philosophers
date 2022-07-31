/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:53:46 by msukri            #+#    #+#             */
/*   Updated: 2022/07/31 16:38:04 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_create(t_value *value);
static int	ft_join(t_value *value);

int	ft_create_join(t_value *value)
{
	int	ret;

	ret = ft_create(value);
	ret = ft_join(value);
	return (ret);
}

static int	ft_create(t_value *value)
{
	t_thread	*thread;
	int			i;

	i = -1;
	while (++i < value->philo)
	{
		thread = ft_thread_handler(value, i);
		if (!thread)
			return (0);
		if (pthread_create(&(value->thread[i]), NULL,
				&routine, (void *)thread) != 0)
		{
			ft_output_err(-3);
			ft_putstr_fd("thread ", 2);
			ft_putnbr_fd(i, 2);
			write(2, "\n", 1);
			return (0);
		}
		usleep(100);
	}
	return (1);
}

static int	ft_join(t_value *value)
{
	int	i;

	i = -1;
	while (++i < value->philo)
	{
		if (pthread_join(value->thread[i], NULL) != 0)
		{
			ft_output_err(-4);
			ft_putstr_fd("thread ", 2);
			ft_putnbr_fd(i, 2);
			write(2, "\n", 1);
			return (0);
		}
	}
	return (1);
}
