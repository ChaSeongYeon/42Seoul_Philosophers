/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seocha <seocha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:28:26 by seocha            #+#    #+#             */
/*   Updated: 2023/04/07 16:28:49 by seocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* memset */
# include <string.h>

/* printf */
# include <stdio.h>

/* malloc, free */
# include <stdlib.h>

/* write, usleep */
# include <unistd.h>

/* gettimeofday */
# include <sys/time.h>

/* pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
	pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock */
# include <pthread.h>

typedef struct s_info
{
	int				num;
	int				flag;
	int				all_eat;
	int				must_cnt;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	long long		t_start;
	pthread_mutex_t	status;
	pthread_mutex_t eat_m;
	pthread_mutex_t flag_m;
	pthread_mutex_t	*forks;
}	t_info;

typedef struct s_phio
{
	int			id;
	int			l_fork;
	int			r_fork;
	int			eat_cnt;
	long long	t_last;
	pthread_t	th;
	t_info		*info;
}	t_philo;

/* simul.c */
void		thread(t_info *info, t_philo *philo);
void		philo_log(t_info *info, t_philo *philo, char *str);

/* error_free.c */
void		exit_error(char *str);
void		check_finished(t_info *info, t_philo *philo);
void		free_thread(t_info *info, t_philo *philo);

/* utils.c */
long long	get_time(void);
int			ft_atoi(const char *str);

#endif