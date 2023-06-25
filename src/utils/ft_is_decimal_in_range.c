#include "../../libft/includes/libft.h"

int	ft_isdecimal(const char *str);
int ft_is_decimal_in_range(const char *str, int low, int high)
{
	int	value;

	value = ft_isdecimal(str);
	if (value >= low && value <= high)
		return (1);
	return (0);
}