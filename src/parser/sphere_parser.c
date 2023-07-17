/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:36:28 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 11:36:44 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	validate_sphere_string(char **data)
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
 	* 0 - `char *` sp
 	* 1 - `t_vector` 3d vector sphere center
 	* 2 - `float` sphere diameter
 	* 3 - `t_color` color vector sphere color
 	* For example: `sp 0.0,0.0,20.6 12.6 10,0,255`
 * @ Input:
 	* t_scene *scene => scene with all data
 	* char **data => strings array represents camera data
 * @ Return value:
 	* return EXIT_SUCCESS if all passed good,
 	* EXIT_FAILED otherwise
 */
int	parse_sphere(t_scene *scene, char **data)
{
	t_sphere	*sphere;
	t_vector	*origin;
	float		radius;
	t_color		*color;

	if (validate_sphere_string(data) == false)
		return (EXIT_FAILURE);
	radius = ft_atof(data[2]);
	if (radius <= 0)
		return (EXIT_FAILURE);
	radius /= 2;
	color = new_color_from_string(data[3]);
	if (!color)
		return (EXIT_FAILURE);
	origin = new_vector_from_strings(data[1]);
	if (!origin)
		return (free_color(color), EXIT_FAILURE);
	sphere = new_sphere(origin, radius, color);
	if (!sphere)
		return (free_color(color), free_vector(origin), EXIT_FAILURE);
	sphere_add_to_scene(scene, sphere);
	return (EXIT_SUCCESS);
}
