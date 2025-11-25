/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalaun <csalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:11:06 by csalaun           #+#    #+#             */
/*   Updated: 2025/10/02 18:00:11 by csalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *p)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (p->id % 2 == 0)
	{
		first = p->fork_r;
		second = p->fork_l;
	}
	else
	{
		first = p->fork_l;
		second = p->fork_r;
	}
	pthread_mutex_lock(first);
	display_status(p, "has taken a fork", 0);
	pthread_mutex_lock(second);
	display_status(p, "has taken a fork", 0);
}

void	eat_sleep(t_philo *p)
{
	t_table	*t;

	t = p->table;
	pthread_mutex_lock(&p->meal_lock);
	p->last_meal = get_time_ms();
	p->meal_count++;
	pthread_mutex_unlock(&p->meal_lock);
	display_status(p, "is eating", 0);
	break_usleep(t, t->time_to_eat);
	pthread_mutex_unlock(p->fork_l);
	pthread_mutex_unlock(p->fork_r);
	display_status(p, "is sleeping", 0);
	break_usleep(t, t->time_to_sleep);
	display_status(p, "is thinking", 0);
	break_usleep(t, t->time_to_think);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;
	t_table	*t;

	p = (t_philo *)arg;
	t = p->table;
	if (t->nb_philo == 1)
	{
		pthread_mutex_lock(&t->forks[0]);
		display_status(p, "has taken a fork", 0);
		break_usleep(t, t->time_to_die);
		pthread_mutex_unlock(&t->forks[0]);
		return (NULL);
	}
	else if (t->nb_philo % 2 == 0 && p->id % 2)
		break_usleep(t, t->time_to_eat / 2);
	else if (t->nb_philo % 2 != 0 && p->id % 2 == 0)
		break_usleep(t, t->time_to_eat);
	while (!get_stop_flag(t))
	{
		take_forks(p);
		eat_sleep(p);
		usleep(500);
	}
	return (NULL);
}
