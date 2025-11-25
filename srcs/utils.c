/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalaun <csalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:11:19 by csalaun           #+#    #+#             */
/*   Updated: 2025/10/02 17:30:18 by csalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

void	break_usleep(t_table *table, int timer)
{
	long long	stop_at;

	stop_at = get_time_ms() + timer;
	while (get_time_ms() < stop_at)
	{
		if (get_stop_flag(table))
			break ;
		usleep(100);
	}
}

int	ft_atoi(const char *s)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	if (!s || !*s)
		return (-1);
	if (s[i] == '+')
		i++;
	if (s[i] == '-')
		return (-1);
	if (s[i] < '0' || s[i] > '9')
		return (-1);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		res = res * 10 + (s[i] - '0');
		if (res > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)res);
}

void	display_status(t_philo *p, char *msg, int is_death)
{
	t_table	*t;

	t = p->table;
	pthread_mutex_lock(&t->stop_lock);
	if (t->stop && !is_death)
	{
		pthread_mutex_unlock(&t->stop_lock);
		return ;
	}
	pthread_mutex_unlock(&t->stop_lock);
	pthread_mutex_lock(&t->print_lock);
	printf("%lld %d %s\n", get_time_ms() - t->start_ms, p->id, msg);
	pthread_mutex_unlock(&t->print_lock);
	if (is_death)
	{
		pthread_mutex_lock(&t->stop_lock);
			t->stop = 1;
		pthread_mutex_unlock(&t->stop_lock);
	}
}
