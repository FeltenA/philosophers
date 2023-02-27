/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:59:59 by afelten           #+#    #+#             */
/*   Updated: 2023/02/19 19:22:36 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	int					id;
	int					nb_eat;
	struct timeval		t_eat;
	pthread_mutex_t		check;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	int					died;
	unsigned long long	t_start;
	t_philo				*philos;
	pthread_t			*philos_t;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write;
	pthread_mutex_t		check;
}	t_data;

#endif
