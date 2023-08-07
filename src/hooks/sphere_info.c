/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:34:19 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/07 18:54:14 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#define SPHERE_OFFSET 200

void	display_spheres_info(t_scene *scene)
{
	char	*to_print;

	if (!scene->spheres)
		return ;
	mlx_string_put(scene->mlx, scene->win, 10, SPHERE_OFFSET + 20, 0xffffff,
		"Sphere:");
	mlx_string_put(scene->mlx, scene->win, 10, SPHERE_OFFSET + 40, 0xffffff,
		"x       y       z");
	to_print = get_coordinates(scene->selected->sphere->center, 2);
	mlx_string_put(scene->mlx, scene->win, 10, SPHERE_OFFSET + 60, 0xffffff,
		to_print);
	free(to_print);
	to_print = get_color_in_hex_string(scene->selected->sphere->color);
	mlx_string_put(scene->mlx, scene->win, 10, SPHERE_OFFSET + 80,
		rgb2int(scene->selected->sphere->color),
		to_print);
	free(to_print);
}
