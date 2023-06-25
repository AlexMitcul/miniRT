
#include "../../includes/minirt.h"

/*
 * @ Description:
 	* Validate that input string is in right format
 	* where format is 'A 0.2 255,255,255' =>
 	* char float color_string
 * @ Input:
 	* char **data => strings array of strings represents ambient light data
 * @ Return value:
 	* return true if is valid, false otherwise
 */
static bool validate_ambient_light_line(char **data)
{
	if (is_float(data[1]) == false || is_color_string(data[2]) == false)
		return (false);
	return (true);
}

/*
 * @ Description:
 	* Parse input strings array, create ambient light structure and assign it
 	* to scene
 * @ Input:
 	* t_scene *scene => scene with all data
 	* char **data => strings array represents ambient light data
 * @ Return value:
 	* return EXIT_SUCCESS if all passed good,
 	* EXIT_FAILED otherwise
 */
int	parse_ambient_light(t_scene *scene, char **data)
{
	t_ambient_light *ambient_light;
	t_color *color;
	float lighting_ratio;

	if (validate_ambient_light_line(data) == false)
		return (EXIT_FAILURE);
	lighting_ratio = ft_atof(data[1]);
	if (lighting_ratio < 0 || lighting_ratio > 1)
		return (handle_error(BAD_VALUE_ERROR, NULL), EXIT_FAILURE);
	color = new_color_from_string(data[2]);
	if (!color)
		return (EXIT_FAILURE);
	ambient_light = (t_ambient_light *) malloc(sizeof(t_ambient_light));
	if (!ambient_light)
		return (free_color(color), handle_error(MEMORY_ERROR, NULL), EXIT_FAILURE);
	ambient_light->color = color;
	ambient_light->lighting_ratio = lighting_ratio;
	scene->ambient_light = ambient_light;
	return (EXIT_SUCCESS);
}