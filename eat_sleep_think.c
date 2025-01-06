/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osadeddi <osadeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:18:38 by osadeddi          #+#    #+#             */
/*   Updated: 2025/01/06 15:27:17 by osadeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_p(t_comb *comb)
{
	pthread_mutex_lock(&comb->data->mutex);
	print_time(comb->philo);
	printf("Philosopher %d is sleeping\n", comb->philo->id);
	pthread_mutex_unlock(&comb->data->mutex);
	my_usleep(comb->data->time_to_sleep * 1000);
}

void	eat(t_comb *comb)
{
	pthread_mutex_lock(&comb->data->mutex);
	print_time(comb->philo);
	printf("Philosopher %d is eating\n", comb->philo->id);
	pthread_mutex_unlock(&comb->data->mutex);
	my_usleep(comb->data->time_to_eat * 1000);
	gettimeofday(&comb->philo->last_meal, NULL);
	// my_usleep(10000); // delete this
}

int	think(t_comb *comb)
{
	pthread_mutex_lock(&comb->data->mutex);
	print_time(comb->philo);
	printf("Philosopher %d is thinking\n", comb->philo->id);
	pthread_mutex_unlock(&comb->data->mutex);
	while (1)
	{
		pthread_mutex_lock(&comb->data->mutex);
		if (!comb->data->status)
		{
			pthread_mutex_unlock(&comb->data->mutex);
			return (0);
		}
		if (comb->data->forks[comb->philo->id - 1]
			&& comb->data->forks[comb->philo->id % comb->data->num_of_philo])
		{
			pthread_mutex_unlock(&comb->data->mutex);
			break ;
		}
		gettimeofday(&comb->philo->end, NULL);
		if ((comb->philo->end.tv_sec * 1000000 + comb->philo->end.tv_usec)
			- (comb->philo->last_meal.tv_sec * 1000000
				+ comb->philo->last_meal.tv_usec) > comb->data->time_to_die
			* 1000)
		{
			print_time(comb->philo);
			printf("Philosopher %d died\n", comb->philo->id);
			comb->data->status = 0;
			free(comb->data->forks);
			free(comb->data->philo);
			free(comb);
			pthread_mutex_unlock(&comb->data->mutex);
			return (0);
		}
		pthread_mutex_unlock(&comb->data->mutex);
	}
	return (1);
}

void	take_forks(t_comb *comb)
{
	pthread_mutex_lock(&comb->data->mutex);
	if (!comb->data->forks[comb->philo->id - 1]
		|| !comb->data->forks[comb->philo->id % comb->data->num_of_philo])
	{
		pthread_mutex_unlock(&comb->data->mutex);
		if (!think(comb))
			err_fun(comb, comb->data, PHILO_DIED);
	}
	else
	{
		comb->data->forks[comb->philo->id - 1] = 0;
		comb->data->forks[comb->philo->id % comb->data->num_of_philo] = 0;
		print_time(comb->philo);
		printf("Philosopher %d has taken a fork\n", comb->philo->id);
		print_time(comb->philo);
		printf("Philosopher %d has taken a fork\n", comb->philo->id);
		pthread_mutex_unlock(&comb->data->mutex);
	}
}

void	return_forks(t_comb *comb)
{
	pthread_mutex_lock(&comb->data->mutex);
	comb->data->forks[comb->philo->id - 1] = 1;
	comb->data->forks[comb->philo->id % comb->data->num_of_philo] = 1;
	pthread_mutex_unlock(&comb->data->mutex);
}
