/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:45:10 by mvpee             #+#    #+#             */
/*   Updated: 2023/12/23 16:21:15 by mvpee            ###   ########.fr       */
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

void	ft_clean(t_data *data)
{
	int i;

	free(data->philo);
	pthread_mutex_destroy(&data->mutex_print);
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
