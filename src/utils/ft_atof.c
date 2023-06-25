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

float			ft_atof(const char *nbr)
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
	sign = nbr[i] == '-' ? 1 : 0;
	i += nbr[i] == '+' || nbr[i] == '-' ? 1 : 0;
	res = ft_atodigit(nbr + i);
	while (nbr[i] != '\0' && nbr[i] != '.')
		i++;
	len = nbr[i] != '\0' ? ft_strlen(nbr + i + 1) + 1 : 1;
	dec = nbr[i] != '\0' ? ft_atodigit(nbr + i + 1) : 0;
	while (--len > 0)
		dec = dec / 10;
	res += dec;
	res = sign == 1 ? -res : res;
	return (res);
}
