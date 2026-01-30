#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data
{
	long	start_time;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		has_a_philo_died;
}				t_data;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t fork_mutex;
}				t_fork;

typedef struct s_thread
{
	int			id;
	pthread_t	philo;
	t_fork		*fork_left;
	t_fork		*fork_right;
	t_data		*data;
	long		last_meal;
}				t_thread;

typedef struct s_monitor
{
	pthread_t	monitor_thread;
	t_data		*data;
	t_thread	**philo_array;
}				t_monitor;

// THREAD ROUTINE ETC
void		take_forks(t_thread *philo, long now);
void		drop_forks(t_thread *philo);
void		*philo_routine(void *args);

// INIT FUNCTIONS
void		init_data(t_data *data);
t_thread	**init_struct_array(int	count, t_data *data);
void		create_pthread(t_thread **philo_array);
t_fork		**init_fork_array(int count);
void		assign_forks(t_fork **fork_array, t_thread **philo_array, int count);

// UTILS
long	get_time();
void	ft_usleep(int sleep);

#endif