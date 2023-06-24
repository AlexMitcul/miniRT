


#include "../../includes/minirt.h"

static bool is_valid_value(char **data)
{
	int x;
	int y;
	int z;

	x = ft_atoi(data[0]);
	y = ft_atoi(data[1]);
	z = ft_atoi(data[2]);
	if (x > 255 || y > 255 || z > 255)
		return (false);
	if (x < 0 || y < 0 || z < 0)
		return (false);
	return (true);
}

/*
 * @ Description: Transform string from format `255,255,255` to struct t_color
 * @ Input: char * in format `255.255.255`
 * @ Output:
 */
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
	if (is_valid_value(splitted) == false)
		return (ft_free_strings(splitted), handle_error(BAD_VALUE_ERROR, NULL), free_color(color), NULL);
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