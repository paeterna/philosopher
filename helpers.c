/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osadeddi <osadeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:49:02 by osadeddi          #+#    #+#             */
/*   Updated: 2025/01/04 21:24:51 by osadeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	err_fun(t_comb *comb,t_data *data, int flag)
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
	if (flag > 1)
	{
		if (data->philo)
			free(data->philo);
		if (data->forks)
			free(data->forks);
		if (comb)
			free(comb);
		pthread_mutex_destroy(&data->mutex);
	}
	exit(1);
}

void	destroys(t_data *data)
{
	pthread_mutex_destroy(&data->mutex);
	free(data->philo);
}

void	print_time(t_philo *philo)
{
	gettimeofday(&philo->end, NULL);
	printf("%ld	", ((philo->end.tv_sec * 1000000 + philo->end.tv_usec)
				- (philo->start.tv_sec * 1000000 + philo->start.tv_usec)) / 1000);
}

void	my_usleep(uint64_t usec)
{
	struct timeval	start;
	struct timeval	current;
	uint64_t		elapsed;

	gettimeofday(&start, NULL);
	elapsed = 0;
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000000
			+ (current.tv_usec - start.tv_usec);
	}
}
