/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadaniel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:27:42 by sadaniel          #+#    #+#             */
/*   Updated: 2026/02/12 12:27:45 by sadaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	long			start_time;
	long			actual_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				has_a_philo_died;
	int				nb_philo;
	int				meals;
	pthread_mutex_t	print_mutex;
}				t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
}				t_fork;

typedef struct s_thread
{
	int				id;
	int				meals_left;
	long			last_meal;
	pthread_t		philo;
	t_fork			*fork_left;
	t_fork			*fork_right;
	t_data			*data;
	pthread_mutex_t	meal_mutex;
}				t_thread;

typedef struct s_monitor
{
	pthread_t	monitor_thread;
	t_data		*data;
	t_thread	**philo_array;
}				t_monitor;

// THREAD ROUTINE ETC
void		*philo_routine(void *args);
void		*philo_routine_must_eat(void *args);
void		*one_philo_routine(void *args);

// INIT FUNCTIONS
t_data		*init_data(int ac, char **av);
t_thread	**init_struct_array(t_data *data, int count, int meals_left);
void		create_pthread(t_thread **philo_array,
				int meals_left, int nb_philo);
t_fork		**init_fork_array(int count);
void		assign_forks(t_fork **fork_array,
				t_thread **philo_array, int count);
t_monitor	*init_monitor(t_monitor *monitor, t_data *data,
				t_thread **philo_array);

// ROUTINE ACTIONS
void		take_fork_right(t_thread *philo);
void		take_fork_left(t_thread *philo);
void		drop_forks(t_thread *philo);
void		eat(t_thread *philo);
void		ft_sleep(t_thread *philo);
void		think(t_thread *philo);

// UTILS
long		get_time(void);
void		ft_usleep(int sleep);
int			ft_atoi(char *str);
int			check_args(char **av);
void		free_all(t_thread **philo_array, t_fork **fork_array,
				t_data *data, t_monitor *monitor);

#endif
