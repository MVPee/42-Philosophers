/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:45:10 by mvpee             #+#    #+#             */
/*   Updated: 2024/01/10 10:43:45 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void	ft_sleep(int time)
{
	int	start;

	start = get_time();
	while (get_time() < (start + time))
		usleep(500);
}

long	get_time()
{
	struct timeval			time;
	static struct timeval	initial_time;

	gettimeofday(&time, NULL);
	if (!initial_time.tv_sec)
	{
		initial_time.tv_sec = time.tv_sec;
		initial_time.tv_usec = time.tv_usec;
	}
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - 
		((initial_time.tv_sec * 1000) + (initial_time.tv_usec / 1000)));
}

void	ft_clean(t_data *data)
{
	int i;

	free(data->philo);
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_fork);
	i = -1;
	while(++i < data->info.number_of_philo)
		pthread_mutex_destroy(&data->philo[i].fork);
}

bool	is_dead(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->info.number_of_philo)
		if (data->philo[i].dead == true)
			return (true);
	return (false);
}
