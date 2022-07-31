/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:53:59 by msukri            #+#    #+#             */
/*   Updated: 2022/07/29 17:23:11 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

# define FORK_TAKEN "My fork!"
# define EATING "Eating!!"
# define SLEEPING "Sleeping"
# define THINKING "Thinking"
# define FULL "I'm full"

# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define CYN "\x1B[36m"

typedef struct s_value
{
	int				philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dying_philo;
	int				eat_freq;
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
	int				*lock;
	pthread_mutex_t	dead_mutex;
}				t_value;

typedef struct s_thread
{
	t_value	*value;
	int		philo_index;
	int		last_meal;
}				t_thread;

int			main(int argc, char **argv);
void		ft_init_value(t_value *value);
int			ft_value_setup(t_value *value, int argc, char **argv);
t_thread	*ft_thread_handler(t_value *value, int i);
long		timer(void);

int			ft_create_join(t_value *value);
void		*routine(void *thread);

int			ft_wait_fork(void *thread, t_value *value, int i);
int			ft_eating(void *thread, t_value *value, int i);
int			ft_unlock_forks(void *thread, t_value *value, int i);
int			ft_sleeping(void *thread, t_value *value, int i);

void		ft_output(t_value *value, int i, char *message);
void		ft_output_1(int i, char *message);

int			ft_dead(void *thread);
int			ft_death(t_value *value, int i);

int			ft_legal_input(char **argv);
int			ft_error(int err, t_value *value);
void		ft_output_err(int err);

int			ft_atoi(const char *str);
int			ft_isnbr(char *nbr);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

void		ft_free_data(t_value *value);

#endif