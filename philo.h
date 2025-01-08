/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osadeddi <osadeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:13:13 by osadeddi          #+#    #+#             */
/*   Updated: 2025/01/08 18:34:17 by osadeddi         ###   ########.fr       */
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
# include <stdint.h>

typedef enum e_error
{
	NO_ARGS,
	INVALID_NUM,
	MALLOC_FAILED,
	THREAD_FAILED,
	JOIN_FAILED,
	MUTEX_FAILED
}				t_error;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
	FORK
}				t_status;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	struct timeval	start;
	struct timeval	end;
	struct timeval	last_meal;
}				t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*forks;
	int				status;
	pthread_mutex_t	forks_m;
	pthread_mutex_t	print_m;
	pthread_mutex_t	status_m;
	t_philo			*philo;
}					t_data;

typedef struct s_comb
{
	t_philo	*philo;
	t_data	*data;
}				t_comb;

int		ft_atoi(const char *str);
void	inits(t_data *data, int argc, char **argv);
void	create_philo(t_data *data);
void	*run_thread(void *data);
void	destroys(t_data *data);
void	err_fun(t_comb *comb, t_data *data, int flag);
void	print_status(t_philo *philo, int status);
int		take_forks(t_comb *comb);
void	return_forks(t_comb *comb);
void	sleeeep(t_comb *comb);
void	eat(t_comb *comb);
int		think(t_comb *comb);
void	my_usleep(uint64_t time, t_comb *comb);
int		check_status(t_comb *comb);
int		check_death(t_comb *comb);

#endif
