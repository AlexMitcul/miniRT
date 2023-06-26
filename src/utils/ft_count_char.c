#include <stddef.h>
#include <stdbool.h>

size_t	ft_count_char(const char *str, char c)
{
	size_t	i;
	size_t	count;

	if (!str)
		return (false);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}