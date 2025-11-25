/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalaun <csalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:10:55 by csalaun           #+#    #+#             */
/*   Updated: 2025/10/02 17:47:00 by csalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_table *t, t_philo *p)
{
	long long	now;

	pthread_mutex_lock(&p->meal_lock);
	now = get_time_ms();
	if (now - p->last_meal > t->time_to_die)
	{
		pthread_mutex_lock(&t->stop_lock);
		t->stop = 1;
		pthread_mutex_unlock(&t->stop_lock);
		usleep(500);
		display_status(p, "died", 1);
		pthread_mutex_unlock(&p->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&p->meal_lock);
	return (0);
}

int	check_meals(t_table *t)
{
	int	i;
	int	full;

	if (t->nb_meal == -1)
		return (0);
	i = 0;
	full = 1;
	while (i < t->nb_philo)
	{
		pthread_mutex_lock(&t->philos[i].meal_lock);
		if (t->philos[i].meal_count < t->nb_meal)
			full = 0;
		pthread_mutex_unlock(&t->philos[i].meal_lock);
		i++;
	}
	if (full)
	{
		pthread_mutex_lock(&t->stop_lock);
		t->stop = 1;
		pthread_mutex_unlock(&t->stop_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table	*t;
	int		i;

	t = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < t->nb_philo)
		{
			if (check_death(t, &t->philos[i]) || check_meals(t))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
