/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osadeddi <osadeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:12:42 by osadeddi          #+#    #+#             */
/*   Updated: 2025/01/04 21:28:54 by osadeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void print_forks(t_data *data)
// {
// 	int i;

// 	pthread_mutex_lock(&data->mutex);
// 	i = 0;
// 	while (i < data->num_of_philo)
// 	{
// 		printf("fork[%d]: %d, ", i, data->forks[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	pthread_mutex_unlock(&data->mutex);
// }

void	*run_thread(void *data)
{
	t_comb	*comb;

	comb = (t_comb *)data;
	if (!comb)
		return (NULL);
	while (comb->data->status)
	{
		// print_forks(comb->data);
		take_forks(comb);
		if (!comb->data->status)
			break ;
		eat(comb);
		if (!comb->data->status)
			break ;
		return_forks(comb);
		if (!comb->data->status)
			break ;
		sleep_p(comb);
		comb->data->status--;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	inits(&data, argc, argv);
	create_philo(&data);
	destroys(&data);
	return (0);
}
