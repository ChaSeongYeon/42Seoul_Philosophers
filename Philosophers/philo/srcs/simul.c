/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seocha <seocha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:24:40 by seocha            #+#    #+#             */
/*   Updated: 2023/04/08 22:22:42 by seocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	take_time(long long time)
{
	long long	start;
	long long	end;

	start = get_time();
	while (1)
	{
		end = get_time();
		if ((end - start) >= time)
			break ;
		usleep(1000);
	}
}

void	philo_log(t_info *info, t_philo *philo, char *str)
{
	long long	now;

	now = get_time();
	pthread_mutex_lock(&(info->status));
	pthread_mutex_lock(&(info->flag_m));
	if (!(info->flag))
		printf("%lld %d %s\n", now - info->t_start, philo->id + 1, str);
	pthread_mutex_unlock(&(info->flag_m));
	pthread_mutex_unlock(&(info->status));
}

static void	eat(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->l_fork]));
	philo_log(info, philo, "has taken a fork");
	pthread_mutex_lock(&(info->flag_m));
	if (info->num != 1 && !(info->flag))
	{
		pthread_mutex_unlock(&(info->flag_m));
		pthread_mutex_lock(&(info->forks[philo->r_fork]));
		philo_log(info, philo, "has taken a fork");
		philo_log(info, philo, "is eating");
		pthread_mutex_lock(&(info->eat_m));
		philo->t_last = get_time();
		(philo->eat_cnt)++;
		pthread_mutex_unlock(&(info->eat_m));
		take_time(info->t_eat);
		pthread_mutex_unlock(&(info->forks[philo->r_fork]));
		pthread_mutex_lock(&(info->flag_m));
	}
	pthread_mutex_unlock(&(info->flag_m));
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
}

static void	*simulation(void *arg)
{
	t_info	*info;
	t_philo	*philo;

	philo = arg;
	info = philo->info;
	if (philo->id % 2)
		usleep(info->t_eat * 1000);
	pthread_mutex_lock(&(info->flag_m));
	while (!(info->flag))
	{
		pthread_mutex_unlock(&(info->flag_m));
		eat(info, philo);
		if (philo->eat_cnt == info->must_cnt)
		{
			info->all_eat++;
			break ;
		}
		philo_log(info, philo, "is sleeping");
		take_time(info->t_sleep);
		philo_log(info, philo, "is thinking");
		usleep(1000);
		pthread_mutex_lock(&(info->flag_m));
	}
	pthread_mutex_unlock(&(info->flag_m));
	return (0);
}

void	thread(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		philo[i].t_last = get_time();
		if (pthread_create(&(philo[i].th), NULL, simulation, &(philo[i])))
			exit_error("Fail to create thread");
		i++;
	}
	check_finished(info, philo);
	i = 0;
	while (i < info->num)
		pthread_join(philo[i++].th, NULL);
	free_thread(info, philo);
}
