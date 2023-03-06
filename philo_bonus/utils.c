/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:43:13 by afelten           #+#    #+#             */
/*   Updated: 2023/03/06 15:43:16 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>

int	philo_print(t_philo *philo, struct timeval time, const char *str);

int	get_nbr(const char *str)
{
	long int	nbr;

	nbr = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - 48;
		if (nbr > 2147483647)
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (nbr);
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
