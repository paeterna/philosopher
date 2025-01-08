/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osadeddi <osadeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:12:48 by osadeddi          #+#    #+#             */
/*   Updated: 2025/01/08 17:55:03 by osadeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(t_data *data)
{
	t_comb	*comb;
	int		i;

	comb = malloc(sizeof(t_comb) * data->num_of_philo);
	if (!comb)
		err_fun(NULL, data, MALLOC_FAILED);
	i = -1;
	while (++i < data->num_of_philo)
	{
		comb[i].philo = &data->philo[i];
		comb[i].data = data;
		if (pthread_create(&data->philo[i].thread, NULL, run_thread, &comb[i]))
			err_fun(comb, data, THREAD_FAILED);
	}
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			err_fun(comb, data, JOIN_FAILED);
	}
	free(comb);
}

static void	philo_init(t_data *data)
{
	int				i;
	struct timeval	now;

	i = -1;
	while (++i < data->num_of_philo)
	{
		gettimeofday(&now, NULL);
		data->forks[i] = 1;
		data->philo[i].id = i + 1;
		data->philo[i].start = now;
		data->philo[i].last_meal = now;
	}
}

void	inits(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		err_fun(NULL, data, NO_ARGS);
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->num_of_philo < 1 || data->time_to_die < 1
		|| data->time_to_eat < 1 || data->time_to_sleep < 1)
		err_fun(NULL, data, INVALID_NUM);
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	data->forks = malloc(sizeof(int) * data->num_of_philo);
	if (!data->philo || !data->forks)
		err_fun(NULL, data, MALLOC_FAILED);
	pthread_mutex_init(&data->print_m, NULL);
	pthread_mutex_init(&data->status_m, NULL);
	pthread_mutex_init(&data->forks_m, NULL);
	philo_init(data);
	data->status = 1;
}
