/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msukri <msukri@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:53:59 by msukri            #+#    #+#             */
/*   Updated: 2022/08/02 19:14:27 by msukri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <wait.h>

# define FORK_TAKEN "My fork!"
# define EATING "Eating!!"
# define SLEEPING "Sleeping"
# define THINKING "Thinking"
# define FULL "I'm full"
# define DIED "Died!!!!"

# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define CYN "\x1B[36m"
# define WHI "\x1B[37m"
# define NC "\x1B[0m"

typedef struct s_philo
{
	int				philo_index;
	struct s_value	*value;
	sem_t			*sem_eat;
	pid_t			philo_pid;
	int				last_meal;
	pthread_t		thread;
}				t_philo;

typedef struct s_value
{
	int				philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_freq;
	sem_t			*sem_fork;
	sem_t			*sem_meal;
	sem_t			*sem_print;
	t_philo			**p;
	pthread_t		full;
}				t_value;

int			main(int argc, char **argv);
void		ft_init_value(t_value *value);
int			ft_value_setup(t_value *value, int argc, char **argv);
long		timer(void);

int			ft_create_join(t_value *value);

void		ft_output(t_value *value, int i, char *message);
void		ft_output_1(int i, char *message);

int			ft_legal_input(char **argv);
int			ft_error(int err, t_value *value);
void		ft_output_err(int err);

int			ft_atoi(const char *str);
int			ft_isnbr(char *nbr);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

void		ft_free_data(t_value *value);

int			ft_sem_init(t_value *value);
t_philo		**ft_philo_init(t_value *value);
void		ft_wait_fork(t_philo *philo);
void		ft_unlock_forks(t_philo *philo);
void		ft_sleeping(t_philo *philo);
void		ft_close_process(t_value *value);

void		*routine(t_philo *philo);
void		*monitor_die(void *philo);
void		*ft_full(void *value);

#endif