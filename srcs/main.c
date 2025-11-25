/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalaun <csalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 23:17:56 by csalaun           #+#    #+#             */
/*   Updated: 2025/10/07 15:07:28 by csalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_table *t)
{
	int			i;
	pthread_t	monitor;

	t->start_ms = get_time_ms();
	i = 0;
	while (i < t->nb_philo)
	{
		t->philos[i].last_meal = t->start_ms;
		if (pthread_create(&t->philos[i].thread, NULL, philo_routine,
				&t->philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, t) != 0)
		return (0);
	pthread_join(monitor, NULL);
	return (1);
}

void	join_threads(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->nb_philo)
	{
		pthread_join(t->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!init_table(&table, argc, argv))
		return (EXIT_FAILURE);
	if (!start_simulation(&table))
	{
		free_all(&table);
		return (EXIT_FAILURE);
	}
	free_all(&table);
	return (EXIT_SUCCESS);
}
