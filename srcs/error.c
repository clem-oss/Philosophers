/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalaun <csalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:10:20 by csalaun           #+#    #+#             */
/*   Updated: 2025/10/02 15:11:11 by csalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_err(const char *msg)
{
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	return (1);
}

int	err_usage(void)
{
	return (print_err("philo: Usage: ./philo <nb_philosopher> <time_to_die> "
			"<time_to_eat> <time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]"));
}

int	err_alloc(void)
{
	return (print_err("Fatal error: allocation failed"));
}

int	err_mutex(void)
{
	return (print_err("Mutex init failed"));
}
