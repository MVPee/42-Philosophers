/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:46:25 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/22 18:42:34 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void eating(t_data *data, int index)
{
	return ;
}

static void	*routine(void *args)
{
	t_all *all = (t_all *)args;
	int index = all->index;
    t_data *data = all->data;

	while(!is_dead(data))
	{
	// 	eating(data, index);
	// 	thinking();
	// 	sleeping();
	}
	return (NULL);
}

bool	threading(t_data *data)
{
	t_all	*all;
	int		i;

	all = (t_all *)malloc(sizeof(t_all) * data->info.number_of_philo);
	if (!all)
		return (printf("malloc failed...\n"), true);
	i = -1;
	while(++i < data->info.number_of_philo)
	{
		all[i].data = data;
		all[i].index = i;
	}
	pthread_mutex_init(&data->mutex_print, NULL);
	i = -1;
	while (++i < data->info.number_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine, &all[i]) != 0)
			return (free(all), printf("pthread create failed...\n"), true);
	}
	i = -1;
	while (++i < data->info.number_of_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (free(all), printf("pthread join failed...\n"), true);
	return (free(all), false);
}
