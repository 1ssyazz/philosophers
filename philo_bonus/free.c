/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:40:39 by msukri            #+#    #+#             */
/*   Updated: 2022/08/02 16:53:37 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_data(t_value *value)
{
	int	i;

	i = -1;
	if (!value)
		return ;
	while (++i < (int)value->philo)
	{
		if (value->p[i])
			free(value->p[i]);
	}
	if (value->p)
		free(value->p);
}
