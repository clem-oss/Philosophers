/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalaun <csalaun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:48:13 by csalaun           #+#    #+#             */
/*   Updated: 2025/10/02 15:58:37 by csalaun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define MAX_PHILO 200

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
	long long		last_meal;
	int				meal_count;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				nb_meal;

	long long		start_ms;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;

	t_philo			*philos;
}	t_table;

/***init***/

int			init_table(t_table *table, int argc, char **argv);
int			init_forks(t_table *t);
int			init_philos(t_table *t);
int			check_args(t_table *table, int argc);
int			philo_died(t_philo *philo);

/***utils***/

long long	get_time_ms(void);
int			ft_atoi(const char *s);
void		break_usleep(t_table *table, int ms);
void		display_status(t_philo *p, char *msg, int is_death);

/***main***/
void		join_threads(t_table *table);

/***error***/
int			print_err(const char *msg);
int			err_usage(void);
int			err_alloc(void);
int			err_mutex(void);

/***free***/
void		set_stop_flag(t_table *table, int status);
void		free_all(t_table *table);
int			get_stop_flag(t_table *table);

/***Monitor***/

int			check_death(t_table *t, t_philo *p);
int			check_meals(t_table *t);
void		*monitor_routine(void *arg);

/***routine***/

void		take_forks(t_philo *p);
void		eat_sleep(t_philo *p);
void		*philo_routine(void *arg);

#endif