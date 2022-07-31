/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:50:28 by msukri            #+#    #+#             */
/*   Updated: 2022/07/31 16:37:41 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_value	value;
	int		i;

	if (!((argc == 5 || argc == 6) && ft_legal_input(argv)))
		return (ft_error(-1, NULL));
	if (ft_atoi(argv[1]) > 4096)
		return (ft_error(-2, NULL));
	ft_init_value(&value);
	if (!(ft_value_setup(&value, argc, argv) && ft_create_join(&value)))
		return (ft_error(-5, &value));
	i = -1;
	while (i++ < value.philo)
		pthread_mutex_destroy(&(value.mutex[i]));
	pthread_mutex_destroy(&(value.dead_mutex));
	ft_free_data(&value);
	return (0);
}
