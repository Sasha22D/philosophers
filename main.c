#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_fork
{
	int	id;
	pthread_mutex_t fork_mutex;
}				t_fork;

typedef struct s_thread
{
	int	id;
	pthread_t	philo;
	t_fork	*fork_left;
	t_fork	*fork_right;
}t_thread;

void	take_forks(t_thread *philo)
{
	printf("Philo %d veut prendre la fourchette de gauche\n", philo->id);
	pthread_mutex_lock(&philo->fork_left->fork_mutex);
	printf("Philo %d a pris la fourchette de gauche\n", philo->id);
	printf("Philo %d veut la fourchette de droite\n", philo->id);
	pthread_mutex_lock(&philo->fork_right->fork_mutex);
	printf("Philo %d a pris la fourchette de droite\n", philo->id);
}

void	drop_forks(t_thread *philo)
{
	pthread_mutex_unlock(&philo->fork_left->fork_mutex);
	printf("Philo %d a poser la fourchette de gauche\n", philo->id);
	pthread_mutex_unlock(&philo->fork_right->fork_mutex);
	printf("Philo %d a poser la fourchette de droite\n", philo->id);
}

void	*philo_routine(void *args)
{
	t_thread	*philo = (t_thread *)args;
	
	// TAKE FORKS ()
	take_forks(philo);
	// EAT()
	printf("Philo %d a manger\n", philo->id);
	// DROP FORKS()
	drop_forks(philo);
	
	// THINK()

	// SLEEP()
	
	return (NULL);
}

t_thread	**init_struct_array(int	count)
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
		// pthread_create(&array[i]->philo, NULL, philo_routine, array[i]);
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
	t_fork		**fork_array;
	int			count;
	int			i;

	i = 0;
	count = atoi(av[1]);
	philo_array = init_struct_array(count);
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