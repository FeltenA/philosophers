
#include "philo_bonus.h"
#include <unistd.h>

int	philo_print(t_philo *philo, struct timeval time, const char *str);

int	get_nbr(const char *str)
{
	int	nbr;
	int	neg;

	nbr = 0;
	neg = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - 48;
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (nbr * neg);
}

int	check_time(t_philo *philo)
{
	struct timeval	t_eat;
	struct timeval	time;

	t_eat.tv_sec = philo->t_eat.tv_sec + philo->data->t_die / 1000;
	t_eat.tv_usec = philo->t_eat.tv_usec + (philo->data->t_die % 1000) * 1000;
	if (t_eat.tv_usec >= 1000000)
	{
		t_eat.tv_sec++;
		t_eat.tv_usec -= 1000000;
	}
	gettimeofday(&time, 0);
	if (time.tv_sec > t_eat.tv_sec || (t_eat.tv_sec == time.tv_sec
			&& time.tv_usec > t_eat.tv_usec))
		return (1);
	return (0);
}

int	print_err(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	return (1);
}