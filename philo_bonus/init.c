/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:52:26 by msukri            #+#    #+#             */
/*   Updated: 2022/08/02 16:43:19 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_value(t_value *value)
{
	value->philo = 0;
	value->time_to_die = 0;
	value->time_to_eat = 0;
	value->time_to_sleep = 0;
	value->eat_freq = 0;
}

int	ft_value_setup(t_value *value, int argc, char **argv)
{
	value->philo = ft_atoi(argv[1]);
	value->time_to_die = ft_atoi(argv[2]);
	value->time_to_eat = ft_atoi(argv[3]);
	value->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		value->eat_freq = ft_atoi(argv[5]);
	if (ft_sem_init(value))
		return (0);
	value->p = ft_philo_init(value);
	return (1);
}

t_philo	**ft_philo_init(t_value *value)
{
	t_philo	**p;
	int		i;

	p = (t_philo **)malloc(sizeof(t_philo *) * value->philo);
	if (!p)
		return (0);
	i = -1;
	while (++i < (int)value->philo)
	{
		p[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
		if (!p[i])
			return (0);
		p[i]->philo_index = i;
		p[i]->value = value;
		sem_unlink("eatcount");
		p[i]->sem_eat = sem_open("eatcount", O_CREAT, 0644, 1);
		if (p[i]->sem_eat == SEM_FAILED)
			return (0);
	}
	return (p);
}

int	ft_sem_init(t_value *value)
{
	sem_unlink("forking");
	value->sem_fork = sem_open("forking", O_CREAT, 0644,
			value->philo);
	if (value->sem_fork == SEM_FAILED)
		return (1);
	sem_unlink("meal");
	value->sem_meal = sem_open("meal", O_CREAT, 0644, 1);
	if (value->sem_meal == SEM_FAILED)
		return (1);
	sem_unlink("print");
	value->sem_print = sem_open("print", O_CREAT, 0644, 1);
	if (value->sem_print == SEM_FAILED)
		return (1);
	return (0);
}

long	timer(void)
{
	struct timeval		time;
	static time_t		start_sec = 0;
	static suseconds_t	start_micro_sec = 0;

	gettimeofday(&time, NULL);
	if (!start_sec)
	{
		start_sec = time.tv_sec;
		start_micro_sec = time.tv_usec;
	}
	return (((time.tv_sec - start_sec) * 1000)
		+ (time.tv_usec - start_micro_sec) / 1000);
}
