/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalaun <csalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:09:20 by csalaun           #+#    #+#             */
/*   Updated: 2025/10/02 16:13:33 by csalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_table *t)
{
	int	i;

	t->forks = malloc(t->nb_philo * sizeof(pthread_mutex_t));
	if (!t->forks)
		return (0);
	i = 0;
	while (i < t->nb_philo)
	{
		if (pthread_mutex_init(&t->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&t->forks[i]);
			free(t->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philos(t_table *t)
{
	int	i;

	t->philos = malloc(t->nb_philo * sizeof(t_philo));
	if (!t->philos)
		return (0);
	i = 0;
	while (i < t->nb_philo)
	{
		t->philos[i].id = i + 1;
		t->philos[i].fork_l = &t->forks[i];
		t->philos[i].fork_r = &t->forks[(i + 1) % t->nb_philo];
		t->philos[i].meal_count = 0;
		t->philos[i].last_meal = 0;
		t->philos[i].table = t;
		if (pthread_mutex_init(&t->philos[i].meal_lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&t->philos[i].meal_lock);
			free(t->philos);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_args(t_table *table, int argc)
{
	if (table->nb_philo < 1 || table->nb_philo > MAX_PHILO
		|| table->time_to_die <= 0
		|| table->time_to_eat <= 0
		|| table->time_to_sleep <= 0
		|| (argc == 6 && table->nb_meal <= 0))
		return (0);
	return (1);
}

int	init_table(t_table *table, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (err_usage(), 0);
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->nb_meal = -1;
	table->time_to_think = (table->nb_philo % 2)
		* (table->time_to_eat - table->time_to_sleep);
	if (argc == 6)
		table->nb_meal = ft_atoi(argv[5]);
	if (!check_args(table, argc))
		return (err_usage(), 0);
	if (!init_forks(table))
		return (err_mutex(), 0);
	if (!init_philos(table))
	{
		free(table->forks);
		return (err_alloc(), 0);
	}
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->stop_lock, NULL);
	table->stop = 0;
	return (1);
}

int	philo_died(t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->meal_lock);
	now = get_time_ms();
	if (now - philo->last_meal > philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}
