/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osadeddi <osadeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:12:42 by osadeddi          #+#    #+#             */
/*   Updated: 2025/01/01 16:20:49 by osadeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_time(t_philo *p)
{
	gettimeofday(&p->end, NULL);
	printf("%ld	", ((p->end.tv_sec * 1000000 + p->end.tv_usec)
			- (p->start.tv_sec * 1000000 + p->start.tv_usec)));
}

void	*run_thread(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (!p)
		return (NULL);
	print_time(p);
	printf("Thread %d is running\n", p->id);
	return (NULL);
}

void	inits(t_philo *p, int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Error: Not enough arguments\n");
		exit(1);
	}
	p->num_of_philo = ft_atoi(argv[1]);
	if (p->num_of_philo < 1)
	{
		printf("Error: Invalid number of philosophers\n");
		exit(1);
	}
	p->philo = malloc(sizeof(pthread_t) * p->num_of_philo);
	if (!p->philo)
	{
		write(2, "Error: Malloc failed\n", 21);
		exit(1);
	}
	gettimeofday(&p->start, NULL);
	pthread_mutex_init(&p->mutex, NULL);
}

void	create_philo(t_philo *p)
{
	int	i;
	t_philo	*philo;

	i = -1;
	while (++i < p->num_of_philo)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
		{
			write(2, "Error: Malloc failed\n", 21);
			exit(1);
		}
		*philo = *p;
		philo->id = i + 1;
		pthread_create(&p->philo[i], NULL, run_thread, philo);
	}
	while (--i > 0)
		pthread_join(p->philo[i - 1], NULL);
}

int	main(int argc, char **argv)
{
	t_philo	p;
	char	*str;

	str = NULL;
	inits(&p, argc, argv);
	create_philo(&p);
	str = strdup("Hello, world!\n");
	if (!str)
		return (1);
	memset(str, 'a', 5);
	printf("%s", str);
	free(str);
	pthread_mutex_destroy(&p.mutex);
	free(p.philo);
	return (0);
}
