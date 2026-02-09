#include "philosophers.h"

void	*philo_routine(void *args)
{
	t_thread	*philo;
	
	philo = (t_thread *)args;
	if (philo->id % 2 != 0)
	{
		printf("0 %d is thinking\n", philo->id);
		ft_usleep(philo->data->time_to_eat);
	}
	while (philo->data->has_a_philo_died == 0)
	{
		if (philo->id % 2 != 0)
		{
			take_fork_right(philo);
			take_fork_left(philo);
		}
		else
		{
			take_fork_left(philo);
			take_fork_right(philo);
		}
		eat(philo);
		drop_forks(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	*one_philo_routine(void *args)
{
	(void)args;
	printf("0 1 has taken a fork\n");
	return (NULL);
}
