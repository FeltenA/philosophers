/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:56:03 by afelten           #+#    #+#             */
/*   Updated: 2023/02/19 19:44:51 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	parse_input(int argc, const char *argv, t_data *data)
{
	data->n_philo = get_nbr(argv[1]);
	data->t_die = get_nbr(argv[2]);
	data->t_eat = get_nbr(argv[3]);
	data->t_sleep = get_nbr(argv[4]);
	if (data->n_philo < 0 || data->t_die < 0 || data->t_eat < 0
		|| data->sleep < 0)
		return (0);
	if (argc == 6)
		data->n_eat = get_nbr(argv[5]);
	else
		data->n_eat = -1;
	if (data->n_eat < 0 && argc == 6)
		return (0);
	return (1);
}

int	create_philo(t_data *data)
{
	data->philos = malloc(sizeof(pthread_t) * data->n_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->philos || !data->forks)
		return (0);
	while (i < data->n_philo)
	{
		data->philos[i] = 
	}
}

int	main(int argc, const char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (parse_input(argc, argv, &data));
		return (1);
}
