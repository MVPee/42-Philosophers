/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:45:10 by mvpee             #+#    #+#             */
/*   Updated: 2024/01/12 11:06:59 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	check_last_eat(t_data *data, int index)
{
	int	now;

	now = get_time(data);
	if (now - data->philo[index].last_eat > data->info.time_to_die)
	{
		print(data, index, DIED);
		return (true);
	}
	return (false);
}

bool	is_died(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->info.number_of_philo)
		if (data->philo[i].dead == true)
			return (true);
	return (false);
}

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

	gettimeofday(&time, NULL);
	result = (time.tv_sec * 1000 + time.tv_usec / 1000) - data->start_time;
	return (result);
}
