
#include "../../includes/minirt.h"

void	parse_ambient_light(t_scene *scene, char **data, size_t line_index)
{
	t_ambient_light *ambient_light;
	t_color *color;
	float lighting_ratio;

	if (ft_atof(&lighting_ratio, data[1]) == EXIT_FAILURE)
		handle_error(PARSER_ERROR, &line_index);
	color = new_color_from_string(data[2]);
	if (!color)
		handle_error(PARSER_ERROR, &line_index);
	ambient_light = (t_ambient_light *) malloc(sizeof(t_ambient_light));
	if (!ambient_light)
	{
		free_color(color);
		handle_error(MEMORY_ERROR, &line_index);
	}
	ambient_light->color = color;
	ambient_light->lighting_ratio = lighting_ratio;
	scene->ambient_light = ambient_light;
}