
#include "philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	check_time(t_philo *philo);

int	philo_print(t_philo *philo, struct timeval time, const char *str)
{
	unsigned long long	timestamp;

	timestamp = time.tv_sec * 1000 + time.tv_usec / 1000;
	timestamp -= philo->data->t_start;
	sem_wait(philo->data->write);
	printf("%llu %d %s\n", timestamp, philo->id + 1, str);
	sem_post(philo->data->write);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	struct timeval	time;

	sem_wait(philo->data->forks);
	gettimeofday(&time, 0);
	philo_print(philo, time, "has taken a fork");
	sem_wait(philo->data->forks);
	gettimeofday(&time, 0);
	philo_print(philo, time, "has taken a fork");
	sem_wait(philo->check);
	gettimeofday(&philo->t_eat, 0);
	philo->nb_eat += 1;
	philo_print(philo, philo->t_eat, "is eating");
	sem_post(philo->check);
	usleep(philo->data->t_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	if (philo->nb_eat == philo->data->n_eat)
	{
		sem_post(philo->data->eaten);
	}
	return (0);
}

void	*check_died(void *arg)
{
	t_philo			*philo;
	struct timeval	time;

	philo = (t_philo *)arg;
	usleep(philo->data->t_die * 1000);
	while (1)
	{
		sem_wait(philo->check);
		if (philo->nb_eat == philo->data->n_eat)
			break ;
		if (check_time(philo))
		{
			gettimeofday(&time, 0);
			philo_print(philo, time, "died");
			sem_post(philo->data->finish);
			break ;
		}
		sem_post(philo->check);
		usleep(5000);
	}
	return (0);
}

void	philosopher(t_philo *philo)
{
	struct timeval	time;
	pthread_t		c_death;

	gettimeofday(&philo->t_eat, 0);
	if (pthread_create(&c_death, 0, check_died, philo))
		exit (0);
	pthread_detach(c_death);
	if (philo->id % 2)
		usleep((philo->data->t_eat / 10) * 1000);
	while (philo->nb_eat != philo->data->n_eat)
	{
		philo_eat(philo);
		gettimeofday(&time, 0);
		philo_print(philo, time, "is sleeping");
		usleep(philo->data->t_sleep * 1000);
		gettimeofday(&time, 0);
		philo_print(philo, time, "is thinking");
		if (philo->data->nb_philo % 2)
			usleep(10000);
	}
	exit(0);
}
