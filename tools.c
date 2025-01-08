/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osadeddi <osadeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:46:51 by osadeddi          #+#    #+#             */
/*   Updated: 2025/01/08 18:24:57 by osadeddi         ###   ########.fr       */
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

void	destroys(t_data *data)
{
	pthread_mutex_destroy(&data->print_m);
	pthread_mutex_destroy(&data->status_m);
	pthread_mutex_destroy(&data->forks_m);
	if (data->forks)
		free(data->forks);
	data->forks = NULL;
	if (data->philo)
		free(data->philo);
	data->philo = NULL;
}

void	my_usleep(uint64_t usec, t_comb *comb)
{
	struct timeval	start;
	struct timeval	current;
	uint64_t		elapsed;

	gettimeofday(&start, NULL);
	elapsed = 0;
	while (elapsed < usec)
	{
		if (!check_death(comb))
			return ;
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000000
			+ (current.tv_usec - start.tv_usec);
	}
}
