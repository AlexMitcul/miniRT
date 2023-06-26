/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:03:57 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/26 10:03:57 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool validate_cylinder_string(char **data)
{
    if (is_vector(data[1], NORMAL) &&
        is_vector(data[2], NORMALIZED) &&
        is_float(data[3]) &&
        is_float(data[4]) &&
        is_color_string(data[5]))
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
int parse_cylinder(t_scene *scene, char **data)
{
    t_cylinder *cylinder;
    t_vector *origin;
    t_vector *direction;
    float radius;
    float height;
    t_color  *color;

    if (validate_cylinder_string(data) == false)
        return (EXIT_FAILURE);
    radius = ft_atof(data[3]);
    height = ft_atof(data[4]);
    if (radius == 0 || height == 0)
        return (EXIT_FAILURE);
    radius /= 2;
    color = new_color_from_string(data[5]);
    if (!color)
        return (EXIT_FAILURE);
    origin = new_vector_from_strings(data[1]);
    if (!origin)
        return (free_color(color), EXIT_FAILURE);
    direction = new_vector_from_strings(data[2]);
    if (!direction)
        return (free_vector(origin), free_color(color), EXIT_FAILURE);
    cylinder = new_cylinder(origin, direction, radius, height, color);
    if (!cylinder)
        return (free_color(color), free_vector(direction),
                free_vector(origin), EXIT_FAILURE);
    cylinder_add_to_scene(scene, cylinder);
    return (EXIT_SUCCESS);
}
