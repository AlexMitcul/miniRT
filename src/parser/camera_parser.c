
#include "../../includes/minirt.h"

// If it will be second camera in scene throw error
void parse_camera(t_scene *scene, char **data, size_t line_index)
{
	t_camera *camera;
	float fov;
	t_vector *origin;
	t_vector *direction;

	origin = parse_vector(data[1]);
	if (origin == NULL)
		handle_error(PARSER_ERROR, &line_index);
	direction = parse_vector(data[2]);
	if (direction == NULL)
	{
		free(origin);
		handle_error(PARSER_ERROR, &line_index);
	}
	fov = ft_atof(data[3]);
	free(direction);
	free(origin);
	handle_error(PARSER_FLOAT_ERROR, &line_index);
	camera = new_camera(origin, direction, fov);
	scene->camera = camera;
}