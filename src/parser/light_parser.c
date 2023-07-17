/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:34:25 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 11:34:56 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static bool	validate_ambient_light_line(char **data)
{
	if (is_float(data[1]) && is_color_string(data[2]))
		return (true);
	return (false);
}

/*
 * @ Description:
 	* Parse input strings array, create ambient light structure and assign it
 	* to scene. Where strings represents
 	* `char` `float` `color_string`
 * @ Input:
 	* t_scene *scene => scene with all data
 	* char **data => strings array represents ambient light data
 * @ Return value:
 	* return EXIT_SUCCESS if all passed good,
 	* EXIT_FAILED otherwise
 */
int	parse_ambient_light(t_scene *scene, char **data)
{
	t_ambient_light	*ambient_light;
	t_color			*color;
	float			lighting;

	if (validate_ambient_light_line(data) == false || scene->ambient_light)
		return (EXIT_FAILURE);
	lighting = ft_atof(data[1]);
	if (lighting < 0 || lighting > 1)
		return (EXIT_FAILURE);
	color = new_color_from_string(data[2]);
	if (!color)
		return (EXIT_FAILURE);
	ambient_light = new_ambient_light(color, lighting);
	if (!ambient_light)
		return (free_color(color), EXIT_FAILURE);
	scene->ambient_light = ambient_light;
	return (EXIT_SUCCESS);
}

static bool	validate_light_string(char **data)
{
	if (is_vector(data[1], NORMAL) && is_float(data[2])
		&& is_color_string(data[3]))
		return (true);
	return (false);
}

/*
 * @ Description:
 	* Parse input strings array, create light structure and assign it
 	* to scene. Where strings represents
 	* 0 - `char` L
 	* 1 - `t_vector` 3d vector
 	* 2 - `float` in [0, 1] light brightness
 	* 3 - `t_color` color vector
 	* For example: `L -40.0,50.0,0.0 0.6 10,0,255`
 * @ Input:
 	* t_scene *scene => scene with all data
 	* char **data => strings array represents camera data
 * @ Return value:
 	* return EXIT_SUCCESS if all passed good,
 	* EXIT_FAILED otherwise
 */
int	parse_light(t_scene *scene, char **data)
{
	t_light		*light;
	t_vector	*origin;
	float		brightness;
	t_color		*color;

	if (validate_light_string(data) == false || scene->light)
		return (EXIT_FAILURE);
	brightness = ft_atof(data[2]);
	if (brightness < 0 || brightness > 1)
		return (EXIT_FAILURE);
	color = new_color_from_string(data[3]);
	if (!color)
		return (EXIT_FAILURE);
	origin = new_vector_from_strings(data[1]);
	if (!origin)
		return (free_color(color), EXIT_FAILURE);
	light = new_light(origin, brightness, color);
	if (!light)
		return (free_vector(origin), free_color(color), EXIT_FAILURE);
	scene->light = light;
	return (EXIT_SUCCESS);
}
