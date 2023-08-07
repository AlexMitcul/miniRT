/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:46:21 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/07 20:19:42 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static double	ft_atodigit(const char *str)
{
	double	res;
	int		i;

	if (str == NULL)
		return (0);
	res = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res = res + (str[i] - '0');
		i++;
	}
	return (res);
}

static int	is_negative(char ch)
{
	if (ch == '-')
		return (1);
	return (0);
}

static int	help_func(bool value, const char *nbr, int i)
{
	if (value)
		return (ft_strlen(nbr + i + 1) + 1);
	return (1);
}

static int	help_func2(bool value, const char *nbr, int i)
{
	if (value)
		return (ft_atodigit(nbr + i + 1));
	return (0);
}

float	ft_atof(const char *nbr)
{
	double	res;
	int		sign;
	double	dec;
	size_t	len;
	int		i;

	i = 0;
	if (nbr == NULL)
		return (0);
	while (nbr[i] && ft_iswhitespace(nbr[i]))
		i++;
	sign = is_negative(nbr[i]);
	i += (nbr[i] == '+' || is_negative(nbr[i]));
	res = ft_atodigit(nbr + i);
	while (nbr[i] != '\0' && nbr[i] != '.')
		i++;
	len = help_func(nbr[i] != '\0', nbr, i);
	dec = help_func2(nbr[i] != '\0', nbr, i);
	while (--len > 0)
		dec = dec / 10;
	res += dec;
	if (sign == 1)
		res = -res;
	return (res);
}
