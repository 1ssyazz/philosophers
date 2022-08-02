/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:53:11 by msukri            #+#    #+#             */
/*   Updated: 2022/08/02 17:17:58 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_legal_input(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (!ft_isnbr(argv[i]) || ft_atoi(argv[i]) < 0)
			return (0);
	}
	return (1);
}

void	ft_output_err(int err)
{
	ft_putstr_fd("Error\n", 2);
	if (err == -1)
		ft_putstr_fd("Invalid input!\n", 2);
	else if (err == -2)
		ft_putstr_fd("Threads exceeded!\n", 2);
	else if (err == -3)
		ft_putstr_fd("pthread create failed!\n", 2);
	else if (err == -4)
		ft_putstr_fd("pthread join failed!\n", 2);
	else if (err == -5)
		ft_putstr_fd("Setup failed!\n", 2);
	else
		ft_putstr_fd("Unknown error\n", 2);
}

int	ft_error(int err, t_value *value)
{
	ft_output_err(err);
	ft_free_data(value);
	return (1);
}
