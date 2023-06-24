
#include "../../includes/minirt.h"

static bool is_valid_str(const char *str)
{
	size_t dots_count;

	if (!str)
		return (false);
	dots_count = 0;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (false);
		if (*str == '.')
			dots_count++;
		if (dots_count > 1)
			return (false);
		str++;
	}
	return (true);
}

// Need to test
int ft_atof(float *to_return, const char *s)
{
	char *dot;
	char *left;
	char *right;
	float result;

	if (is_valid_str(s) == false)
		return (EXIT_FAILURE);
	dot = ft_strchr(s, '.');
	if (!dot)
		return ((float) ft_atoi(s));
	left = ft_substr(s, 0, (dot - s) / sizeof(char));
	right = ft_strdup(dot + 1);
	result = ft_atoi(left) + (ft_atoi(right) / ft_strlen(right));
	*to_return = result;
	return (EXIT_SUCCESS);
}
