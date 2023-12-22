/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:46:25 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/22 17:17:20 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*routine(void *args)
{
	t_all *all = (t_all *)args;
	t_philo philo = all->philo;
    t_data *data = all->data;

	pthread_mutex_lock(&data->mutex_eat);
	printf("id: %d\n", philo.id);
	pthread_mutex_unlock(&data->mutex_eat);
	return (NULL);
}

int	threading(t_data *data)
{
	t_all	all;
	int		i;

	all.data = data;
	pthread_mutex_init(&data->mutex_eat, NULL);
	i = -1;
	while (++i < data->info.number_of_philo)
	{
		all.philo = data->philo[i];
		if (pthread_create(&data->philo[i].thread, NULL, &routine, (void *)&all) != 0)
			return (printf("pthread create failed...\n"), 1);
	}
	i = -1;
	while (++i < data->info.number_of_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (printf("pthread join failed...\n"), 1);
	return (0);
}
