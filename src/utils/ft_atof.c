
#include "../../includes/minirt.h"

int ft_atof(float *result, const char* str) {
	float fraction = 0.0f;
	int sign = 1;
	int divisor = 1;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		*result = *result * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		fraction = fraction * 10 + (*str - '0');
		divisor *= 10;
		str++;
	}
	*result += (fraction / divisor) * sign;
	return (EXIT_SUCCESS);
}
