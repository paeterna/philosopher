/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osadeddi <osadeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:13:13 by osadeddi          #+#    #+#             */
/*   Updated: 2025/01/01 16:23:44 by osadeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				num_of_philo;
	pthread_t		*philo;
	pthread_mutex_t	mutex;
	struct timeval	start;
	struct timeval	end;
}					t_philo;

int	ft_atoi(const char *str);

#endif
