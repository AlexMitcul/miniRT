#include "../../includes/minirt.h"

bool is_float(const char* str)
{
	bool digits_found;

	if (*str == '+' || *str == '-')
		str++;
	digits_found = false;
	while (ft_isdigit(*str))
	{
		digits_found = true;
		str++;
	}
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*(str - 1) == '.')
		return (false);
	return (digits_found && !(*str));
}