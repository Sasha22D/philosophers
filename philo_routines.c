#include "philosophers.h"

void	*philo_routine(void *args)
{
	t_thread	*philo = (t_thread *)args;

	if (philo->id % 2 != 0)
	{
		printf("0 %d is thinking\n", philo->id);
		ft_usleep(philo->data->time_to_eat);
	}
	while (philo->data->has_a_philo_died == 0)
	{
		take_fork_left(philo);
		take_fork_right(philo);
		eat(philo);
		drop_forks(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	*philo_routine_must_eat(void *args)
{
	t_thread	*philo = (t_thread *)args;

	if (philo->id % 2 != 0)
	{
		printf("0 %d is thinking\n", philo->id);
		ft_usleep(philo->data->time_to_eat);
	}
	while (philo->data->has_a_philo_died == 0 && philo->meals_left > 0)
	{
		take_fork_left(philo);
		take_fork_right(philo);
		eat(philo);
		philo->meals_left--;
		printf("%d meals left\n", philo->meals_left);
		drop_forks(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}
