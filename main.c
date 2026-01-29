#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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
}				t_thread;

long	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int sleep)
{
	long long	start;
	long long	now;

	start = get_time();
	now = 0;
	while (now - start < sleep)
		now = get_time();
}

void	init_data(t_data *data)
{
	data->has_a_philo_died = 0;
	data->start_time = get_time();
	data->time_to_eat = 200;
	data->time_to_sleep = 200;
}

void	take_forks(t_thread *philo, long now)
{
	pthread_mutex_lock(&philo->fork_left->fork_mutex);
	printf("%ld %d has taken left fork\n", now - philo->data->start_time, philo->id);
	pthread_mutex_lock(&philo->fork_right->fork_mutex);
	printf("%ld %d has taken right fork\n", now - philo->data->start_time, philo->id);
}

void	drop_forks(t_thread *philo)
{
	long	now;

	now = get_time();
	pthread_mutex_unlock(&philo->fork_left->fork_mutex);
	printf("%ld %d dropped left fork\n", now - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->fork_right->fork_mutex);
	printf("%ld %d dropped right fork\n", now - philo->data->start_time, philo->id);
}

void	*philo_routine(void *args)
{
	t_thread	*philo = (t_thread *)args;
	long		now;

	if (philo->id % 2 != 0)
		ft_usleep(philo->data->time_to_eat);
	while (philo->data->has_a_philo_died == 0)
	{
		now = get_time();
		// TAKE FORKS ()
		take_forks(philo, now);
		// EAT()
		ft_usleep(philo->data->time_to_eat);
		printf("%ld %d is eating\n", get_time() - philo->data->start_time, philo->id);
		// DROP FORKS()
		drop_forks(philo);
		
		// THINK()
		ft_usleep(200);
	
		// SLEEP()
		ft_usleep(philo->data->time_to_sleep);
	}
	
	return (NULL);
}

t_thread	**init_struct_array(int	count, t_data *data)
{
	t_thread	**array;
	int			i;

	i = 0;
	array = malloc(sizeof(t_thread *) * count);
	if (!array)
		return (NULL);
	while (i < count)
	{
		array[i] = malloc(sizeof(t_thread));
		array[i]->id = i + 1;
		array[i]->data = data;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	create_pthread(t_thread **philo_array)
{
	int	i;

	i = 0;
	while (philo_array[i])
	{
		pthread_create(&philo_array[i]->philo, NULL, philo_routine, philo_array[i]);
		i++;
	}
}

t_fork	**init_fork_array(int count)
{
	t_fork	**array;
	int		i;

	i = 0;
	array = malloc(sizeof(t_fork *) * count);
	if (!array)
		return (NULL);
	while (i < count)
	{
		array[i] = malloc(sizeof(t_fork));
		array[i]->id = i + 1;
		pthread_mutex_init(&array[i]->fork_mutex, NULL);
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	assign_forks(t_fork **fork_array, t_thread **philo_array, int count)
{
	int	i;

	i = 0;
	while (philo_array[i])
	{
		if (i == 0)
		{
			philo_array[i]->fork_left = fork_array[i];
			philo_array[i]->fork_right = fork_array[i + 1];
		}
		else if (i == count - 1)
		{
			philo_array[i]->fork_left = fork_array[i];
			philo_array[i]->fork_right = fork_array[0];
		}
		else
		{
			philo_array[i]->fork_left = fork_array[i];
			philo_array[i]->fork_right = fork_array[i + 1];
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	(void)ac;
	t_thread	**philo_array;
	t_data		*data;
	t_fork		**fork_array;
	int			count;
	int			i;

	data = malloc(sizeof(t_data));

	i = 0;
	count = atoi(av[1]);
	init_data(data);
	philo_array = init_struct_array(count, data);
	fork_array = init_fork_array(count);
	assign_forks(fork_array, philo_array, count);
	create_pthread(philo_array);
	
	i = 0;
	while (i < count)
	{
		pthread_join(philo_array[i]->philo, NULL);
		i++;
	}
}
