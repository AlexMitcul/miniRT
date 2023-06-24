
#include "../../includes/minirt.h"

int	parse_ambient_light(t_scene *scene, char **data)
{
	t_ambient_light *ambient_light;
	t_color *color;
	float lighting_ratio;

	if (ft_atof(&lighting_ratio, data[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
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