/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osadeddi <osadeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:12:42 by osadeddi          #+#    #+#             */
/*   Updated: 2025/01/08 17:54:42 by osadeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run_thread(void *data)
{
	t_comb	*comb;

	comb = (t_comb *)data;
	if (!comb)
		return (NULL);
	while (1)
	{
		if (!take_forks(comb))
			return (NULL);
		eat(comb);
		return_forks(comb);
		sleeeep(comb);
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
