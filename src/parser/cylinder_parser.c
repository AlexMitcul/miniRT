/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:03:57 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/07 20:11:16 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	validate_cylinder_string(char **data)
{
	if (is_vector(data[1], NORMAL) && is_vector(data[2], NORMALIZED)
		&& is_float(data[3]) && is_float(data[4]) && is_color_string(data[5]))
		return (true);
	return (false);
}

/*
 * @ Description:
 	* Parse input strings array, create cylinder structure and assign it
 	* to scene. Where strings represents
 	* 0 - `char *` cy
 	* 1 - `t_vector` 3d vector plane origin
 	* 2 - `t_vector` 3d vector normalized.
 	* 3 - `float` cylinder radius
 	* 4 - `float` cylinder height
 	* 5 - `t_color` color vector cylinder color
 	* For example: `cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255`
 * @ Input:
 	* t_scene *scene => scene with all data
 	* char **data => strings array represents camera data
 * @ Return value:
 	* return EXIT_SUCCESS if all passed good,
 	* EXIT_FAILED otherwise
 */

static int	parse_cylinder2(t_scene *scene, char **data, t_cylinder *cylinder,
	float num_data[2])
{
	t_vector	*origin;
	t_vector	*direction;
	t_color		*color;

	color = new_color_from_string(data[5]);
	if (!color)
		return (EXIT_FAILURE);
	origin = new_vector_from_strings(data[1]);
	if (!origin)
		return (free_color(color), EXIT_FAILURE);
	direction = new_vector_from_strings(data[2]);
	if (!direction)
		return (free_vector(origin), free_color(color), EXIT_FAILURE);
	cylinder = new_cylinder(origin, direction, num_data, color);
	if (!cylinder)
		return (free_color(color), free_vector(direction), free_vector(origin),
			EXIT_FAILURE);
	cylinder_add_to_scene(scene, cylinder);
	return (EXIT_SUCCESS);
}

int	parse_cylinder(t_scene *scene, char **data)
{
	t_cylinder	*cylinder;
	float		num_data[2];

	cylinder = NULL;
	if (validate_cylinder_string(data) == false)
		return (EXIT_FAILURE);
	num_data[0] = ft_atof(data[3]);
	num_data[1] = ft_atof(data[4]);
	if (num_data[0] == 0 || num_data[1] == 0)
		return (EXIT_FAILURE);
	num_data[0] /= 2;
	return (parse_cylinder2(scene, data, cylinder, num_data));
}
