/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 09:00:44 by kpolojar          #+#    #+#             */
/*   Updated: 2022/09/30 14:47:53 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_calculate_output(char *str, int sign, int i)
{
	long	nb;

	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		if (nb > INT_MAX && sign > 0)
		{
			ft_putendl("Too large number for atoi!");
			exit(-1);
		}
		if (-nb < INT_MIN && sign < 0)
		{
			ft_putendl("Too small number for atoi!");
			exit(-1);
		}
		i++;
	}
	return (nb);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	nb;
	int		i;

	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = sign * -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	nb = ft_calculate_output((char *)str, sign, i);
	return (sign * nb);
}
