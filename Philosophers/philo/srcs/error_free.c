/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seocha <seocha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:28:56 by seocha            #+#    #+#             */
/*   Updated: 2023/04/07 16:29:59 by seocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	exit_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	check_finished(t_info *info, t_philo *philo)
{
	int			i;
	long long	now;

	pthread_mutex_lock(&(info->flag_m));
	while (!(info->flag))
	{
		pthread_mutex_unlock(&(info->flag_m));
		i = 0;
		if ((info->must_cnt != 0) && (info->all_eat == info->num))
		{	
			pthread_mutex_lock(&(info->flag_m));
			info->flag = 1;
			break ;
		}
		while (i < info->num)
		{
			now = get_time();
			pthread_mutex_lock(&(info->eat_m));
			if ((now - philo[i].t_last) >= info->t_die)
			{
				pthread_mutex_unlock(&(info->eat_m));
				philo_log(info, philo, "died");
				pthread_mutex_lock(&(info->flag_m));
				info->flag = 1;
				pthread_mutex_unlock(&(info->flag_m));
				break ;
			}
			pthread_mutex_unlock(&(info->eat_m));
			pthread_mutex_unlock(&(info->eat_m));
			i++;
		}
		pthread_mutex_lock(&(info->flag_m));
	}
	pthread_mutex_unlock(&(info->flag_m));
}

void	free_thread(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		pthread_mutex_destroy(&(info->forks[i]));
		i++;
	}
	free(philo);
	free(info->forks);
	pthread_mutex_destroy(&(info->status));
	pthread_mutex_destroy(&(info->flag_m));
	pthread_mutex_destroy(&(info->eat_m));
}
