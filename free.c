/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:40:39 by msukri            #+#    #+#             */
/*   Updated: 2022/07/29 17:17:34 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_data(t_value *value)
{
	if (!value)
		return ;
	if (value->thread)
		free(value->thread);
	if (value->mutex)
		free(value->mutex);
	if (value->lock)
		free(value->lock);
}
