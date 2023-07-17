/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:57:55 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 11:36:01 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	validate_plane_string(char **data)
{
	if (is_vector(data[1], NORMAL) && is_vector(data[2], NORMALIZED)
		&& is_color_string(data[3]))
		return (true);
	return (false);
}

/*
 * @ Description:
 	* Parse input strings array, create plane structure and assign it
 	* to scene. Where strings represents
 	* 0 - `char *` pl
 	* 1 - `t_vector` 3d vector plane origin
 	* 2 - `t_vector` 3d vector normalized.
 	* 3 - `t_color` color vector plane color
 	* For example: `pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225`
 * @ Input:
 	* t_scene *scene => scene with all data
 	* char **data => strings array represents camera data
 * @ Return value:
 	* return EXIT_SUCCESS if all passed good,
 	* EXIT_FAILED otherwise
 */
int	parse_plane(t_scene *scene, char **data)
{
	t_plane		*plane;
	t_vector	*origin;
	t_vector	*direction;
	t_color		*color;

	if (validate_plane_string(data) == false)
		return (EXIT_FAILURE);
	color = new_color_from_string(data[3]);
	if (!color)
		return (EXIT_FAILURE);
	origin = new_vector_from_strings(data[1]);
	if (!origin)
		return (free_color(color), EXIT_FAILURE);
	direction = new_vector_from_strings(data[2]);
	if (!direction)
		return (free_vector(origin), free_color(color), EXIT_FAILURE);
	plane = new_plane(origin, direction, color);
	if (!plane)
		return (free_color(color), free_vector(direction), free_vector(origin),
			EXIT_FAILURE);
	plane_add_to_scene(scene, plane);
	return (EXIT_SUCCESS);
}
