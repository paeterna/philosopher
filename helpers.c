/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osadeddi <osadeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:49:02 by osadeddi          #+#    #+#             */
/*   Updated: 2025/01/08 18:06:49 by osadeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_comb *comb)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if ((now.tv_sec * 1000 + now.tv_usec / 1000)
		- (comb->philo->last_meal.tv_sec * 1000 + comb->philo->last_meal.tv_usec
			/ 1000) > comb->data->time_to_die)
	{
		pthread_mutex_lock(&comb->data->print_m);
		if (!check_status(comb))
		{
			pthread_mutex_unlock(&comb->data->print_m);
			return (0);
		}
		pthread_mutex_lock(&comb->data->status_m);
		comb->data->status = 0;
		print_time(comb->philo, DEAD);
		pthread_mutex_unlock(&comb->data->status_m);
		pthread_mutex_unlock(&comb->data->print_m);
		return (0);
	}
	return (1);
}

void	err_fun(t_comb *comb, t_data *data, int flag)
{
	if (flag == 0)
		printf("Error: No arguments\n");
	else if (flag == 1)
		printf("Error: Invalid number\nall numbers should be greater than 0\n");
	else if (flag == 2)
		printf("Error: Malloc failed\n");
	else if (flag == 3)
		printf("Error: Thread creation failed\n");
	else if (flag == 4)
		printf("Error: Thread join failed\n");
	else if (flag == 5)
		printf("Error: Mutex failed\n");
	if (flag > 1)
	{
		destroys(data);
		if (comb)
			free(comb);
		comb = NULL;
	}
	exit(1);
}

void	print_time(t_philo *philo, int status)
{
	gettimeofday(&philo->end, NULL);
	printf("%ld	", ((philo->end.tv_sec * 1000000 + philo->end.tv_usec)
			- (philo->start.tv_sec * 1000000 + philo->start.tv_usec))
		/ 1000);
	if (status == 0)
		printf("Philosopher %d is eating\n", philo->id);
	else if (status == 1)
		printf("Philosopher %d is sleeping\n", philo->id);
	else if (status == 2)
		printf("Philosopher %d is thinking\n", philo->id);
	else if (status == 3)
		printf("Philosopher %d died\n", philo->id);
	else if (status == 4)
		printf("Philosopher %d has taken a fork\n", philo->id);
}

int	check_status(t_comb *comb)
{
	int	current_status;

	pthread_mutex_lock(&comb->data->status_m);
	current_status = comb->data->status;
	pthread_mutex_unlock(&comb->data->status_m);
	return (current_status);
}
