/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seocha <seocha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:30:42 by seocha            #+#    #+#             */
/*   Updated: 2023/06/20 17:41:03 by seocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(info->status), NULL))
		return (exit_error("Status mutex error."));
	if (pthread_mutex_init(&(info->flag_m), NULL))
		return (exit_error("Flag mutex error."));
	if (pthread_mutex_init(&(info->eat_m), NULL))
		return (exit_error("Eat mutex error."));
	if (pthread_mutex_init(&(info->cnt_m), NULL))
		return (exit_error("Count mutex error."));
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num);
	if (!(info->forks))
		return (exit_error("Malloc error."));
	while (i < info->num)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
			return (exit_error("Fork mutex error."));
		i++;
	}
	return (0);
}

static int	init_info(t_info *info, int argc, char *argv[])
{
	info->num = ft_atoi(argv[1]);
	if (info->num == 0)
		return (exit_error("There must be at least one philosopher."));
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	if (info->num == -1 || info->t_die == -1 || info->t_eat == -1 \
	|| info->t_sleep == -1)
		return (-1);
	info->flag = 0;
	info->all_eat = 0;
	info->t_start = get_time();
	if (argc == 6)
	{
		info->must_cnt = ft_atoi(argv[5]);
		if (info->must_cnt == -1)
			return (-1);
		if (info->must_cnt == 0)
			return (exit_error("Optional argument must be greater than zero."));
	}
	else
		info->must_cnt = 0;
	init_mutex(info);
	return (0);
}

static int	init_philo(t_info *info, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * info->num);
	if (!(*philo))
		return (exit_error("Malloc error."));
	while (i < info->num)
	{
		(*philo)[i].id = i;
		(*philo)[i].l_fork = i;
		(*philo)[i].r_fork = (i + 1) % info->num;
		(*philo)[i].t_last = 0;
		(*philo)[i].eat_cnt = 0;
		(*philo)[i].info = info;
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
	{
		printf("%s\n", "Argument error.");
		return (-1);
	}
	if (init_info(&info, argc, argv) == -1)
		return (1);
	if (init_philo(&info, &philo) == -1)
		return (1);
	if (thread(&info, philo) == -1)
		return (1);
	return (0);
}
