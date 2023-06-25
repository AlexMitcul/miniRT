
#include "../../includes/minirt.h"

static bool	validate_camera_line(char **data)
{
	if (is_vector(data[1], NORMAL) &&
		is_vector(data[2], NORMALIZED) &&
		is_float(data[3]))
		return (true);
	return (false);
}

//! If it will be second camera in scene throw error
/*
 * @ Description:
 	* Parse input strings array, create camera structure and assign it
 	* to scene. Where strings represents
 	* 0 - `char` C
 	* 1 - `t_vector` 3d vector
 	* 2 - `t_vector` 3d normalized vector where [-1, 1] for each coordinate
 	* 3 - `char` in [0, 180]
 	* For example: `C -50.0,0,20 0,0,1 70`
 * @ Input:
 	* t_scene *scene => scene with all data
 	* char **data => strings array represents camera data
 * @ Return value:
 	* return EXIT_SUCCESS if all passed good,
 	* EXIT_FAILED otherwise
 */
int parse_camera(t_scene *scene, char **data)
{
	t_camera *camera;
	t_vector *origin;
	t_vector *direction;
	float	fov;

	if (validate_camera_line(data) == false || scene->camera)
		return (EXIT_FAILURE);
	fov = ft_atof(data[3]);
	if (fov < 0 || fov > 180)
		return (EXIT_FAILURE);
	origin = new_vector_from_strings(data[1]);
	if (!origin)
		return (EXIT_FAILURE);
	direction = new_vector_from_strings(data[2]);
	if (!direction)
		return (free_vector(origin), EXIT_FAILURE);
	camera = (t_camera *) malloc(sizeof(t_camera));
	camera->origin = origin;
	camera->direction = direction;
	camera->fov = fov;
	scene->camera = camera;
	return (EXIT_SUCCESS);
}