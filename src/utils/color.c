


#include "../../includes/minirt.h"


t_color *new_color_from_string(const char *data)
{
	char **splitted;
	t_color *color;
	size_t count;

	splitted = ft_split(data, ',');
	if (!splitted)
		return (NULL);
	count = 0;
	while (splitted[count] && ft_isdecimal(splitted[count]))
		count++;
	if (count != 3)
		return (ft_free_strings(splitted), NULL);
	color = (t_color *) malloc(sizeof(t_color));
	if (!color)
		return (ft_free_strings(splitted), handle_error(MEMORY_ERROR, NULL), NULL);
	color->r = ft_atoi(splitted[0]);
	color->g = ft_atoi(splitted[1]);
	color->b = ft_atoi(splitted[2]);
	return (color);
}

void	free_color(t_color *color)
{
	if (!color)
		return ;
	free(color);
}