#include "../../includes/minirt.h"

bool is_color_string(const char *line)
{
	char	**splitted;
	size_t	count;

	splitted = ft_split(line, ',');
	if (!splitted || !(*splitted))
		return (false);
	count = 0;
	while (splitted[count] && ft_isdecimal(splitted[count]))
		count++;
	if (count != 3)
		return (false);
	return (true);
}