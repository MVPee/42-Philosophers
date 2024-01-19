/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:45:10 by mvpee             #+#    #+#             */
/*   Updated: 2024/01/19 13:56:11 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	unsigned long	nbr;
	int				sign;

	sign = 1;
	nbr = 0;
	while ((*nptr != '\0') && ((*nptr == 32) || (*nptr >= 9 && *nptr <= 13)))
		nptr++;
	if (*nptr == 45)
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == 43)
		nptr++;
	while ((*nptr != '\0') && (*nptr >= 48 && *nptr <= 57))
	{
		nbr = (nbr * 10) + (*nptr - 48);
		nptr++;
		if ((nbr > LONG_MAX) && (sign == 1))
			return (-1);
		else if ((nbr > LONG_MAX) && (sign == -1))
			return (0);
	}
	return (nbr * sign);
}

bool	has_died(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->mutex_data);
	while (++i < (int) data->info.number_of_philo)
		if (data->philo[i].dead == true)
			return (pthread_mutex_unlock(&data->mutex_data), true);
	return (pthread_mutex_unlock(&data->mutex_data), false);
}

void	ft_sleep(t_data *data, int time)
{
	int	start;

	start = get_time(data);
	while (get_time(data) < start + time)
		usleep(100);
}

int	get_time(t_data *data)
{
	int				result;
	struct timeval	time;
	struct timeval	start;

	pthread_mutex_lock(&data->mutex_time);
	if (!data->start_time)
	{
		gettimeofday(&start, NULL);
		data->start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
	}
	gettimeofday(&time, NULL);
	result = (time.tv_sec * 1000 + time.tv_usec / 1000) - data->start_time;
	pthread_mutex_unlock(&data->mutex_time);
	return (result);
}

t_all	*get_all_informations(t_data *data)
{
	t_all	*all;
	int		i;

	all = (t_all *)malloc(sizeof(t_all) * data->info.number_of_philo);
	if (!all)
		return (printf("malloc failed...\n"), NULL);
	i = -1;
	while (++i < (int) data->info.number_of_philo)
	{
		all[i].data = data;
		all[i].index = i;
	}
	return (all);
}
