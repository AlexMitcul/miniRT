
#include "../../includes/minirt.h"

// check!
bool is_float(const char* str) {
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
	return digits_found && !(*str);
}

int	parse_ambient_light(t_scene *scene, char **data)
{
	t_ambient_light *ambient_light;
	t_color *color;
	float lighting_ratio;

	lighting_ratio = 0.0;
	if (ft_atof(&lighting_ratio, data[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (lighting_ratio < 0.0 || lighting_ratio > 1.0)
		return (handle_error(BAD_VALUE_ERROR, NULL), EXIT_FAILURE);
	color = new_color_from_string(data[2]);
	if (!color)
		return (EXIT_FAILURE);
	ambient_light = (t_ambient_light *) malloc(sizeof(t_ambient_light));
	if (!ambient_light)
	{
		free_color(color);
		return (handle_error(MEMORY_ERROR, NULL), EXIT_FAILURE);
	}
	ambient_light->color = color;
	ambient_light->lighting_ratio = lighting_ratio;
	scene->ambient_light = ambient_light;
	return (EXIT_SUCCESS);
}