/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osadeddi <osadeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:18:38 by osadeddi          #+#    #+#             */
/*   Updated: 2025/01/08 18:25:41 by osadeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeeep(t_comb *comb)
{
	pthread_mutex_lock(&comb->data->print_m);
	if (!check_status(comb))
	{
		pthread_mutex_unlock(&comb->data->print_m);
		return ;
	}
	print_time(comb->philo, SLEEP);
	pthread_mutex_unlock(&comb->data->print_m);
	my_usleep(comb->data->time_to_sleep * 1000, comb);
}

void	eat(t_comb *comb)
{
	gettimeofday(&comb->philo->last_meal, NULL);
	pthread_mutex_lock(&comb->data->print_m);
	if (!check_status(comb))
	{
		pthread_mutex_unlock(&comb->data->print_m);
		return ;
	}
	print_time(comb->philo, EAT);
	pthread_mutex_unlock(&comb->data->print_m);
	my_usleep(comb->data->time_to_eat * 1000, comb);
}

int	think(t_comb *comb)
{
	pthread_mutex_lock(&comb->data->print_m);
	if (!check_status(comb))
	{
		pthread_mutex_unlock(&comb->data->print_m);
		return (0);
	}
	print_time(comb->philo, THINK);
	pthread_mutex_unlock(&comb->data->print_m);
	while (1)
	{
		if (!check_status(comb))
			return (0);
		pthread_mutex_lock(&comb->data->forks_m);
		if (comb->data->forks[comb->philo->id - 1]
			&& comb->data->forks[comb->philo->id % comb->data->num_of_philo])
		{
			pthread_mutex_unlock(&comb->data->forks_m);
			return (1);
		}
		pthread_mutex_unlock(&comb->data->forks_m);
		if (!check_death(comb))
			return (0);
	}
	return (1);
}

int	take_forks(t_comb *comb)
{
	while (1)
	{
		if (!check_status(comb))
			return (0);
		pthread_mutex_lock(&comb->data->forks_m);
		if (comb->data->forks[comb->philo->id - 1]
			&& comb->data->forks[comb->philo->id % comb->data->num_of_philo])
		{
			comb->data->forks[comb->philo->id - 1] = 0;
			comb->data->forks[comb->philo->id % comb->data->num_of_philo] = 0;
			pthread_mutex_unlock(&comb->data->forks_m);
			pthread_mutex_lock(&comb->data->print_m);
			if (!check_status(comb))
				return (pthread_mutex_unlock(&comb->data->print_m));
			print_time(comb->philo, FORK);
			print_time(comb->philo, FORK);
			pthread_mutex_unlock(&comb->data->print_m);
			break ;
		}
		pthread_mutex_unlock(&comb->data->forks_m);
		if (!think(comb))
			return (0);
	}
	return (1);
}

void	return_forks(t_comb *comb)
{
	if (!check_status(comb))
		return ;
	pthread_mutex_lock(&comb->data->forks_m);
	comb->data->forks[comb->philo->id - 1] = 1;
	comb->data->forks[comb->philo->id % comb->data->num_of_philo] = 1;
	pthread_mutex_unlock(&comb->data->forks_m);
}
