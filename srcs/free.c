/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalaun <csalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:49:46 by csalaun           #+#    #+#             */
/*   Updated: 2025/10/02 15:11:26 by csalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_table *t)
{
	int	i;

	if (!t)
		return ;
	join_threads(t);
	i = 0;
	while (i < t->nb_philo)
	{
		pthread_mutex_destroy(&t->philos[i].meal_lock);
		i++;
	}
	i = 0;
	while (i < t->nb_philo)
	{
		pthread_mutex_destroy(&t->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&t->print_lock);
	pthread_mutex_destroy(&t->stop_lock);
	free(t->philos);
	free(t->forks);
}

void	set_stop_flag(t_table *table, int status)
{
	pthread_mutex_lock(&table->stop_lock);
	table->stop = status;
	pthread_mutex_unlock(&table->stop_lock);
}

int	get_stop_flag(t_table *table)
{
	int	val;

	pthread_mutex_lock(&table->stop_lock);
	val = table->stop;
	pthread_mutex_unlock(&table->stop_lock);
	return (val);
}
