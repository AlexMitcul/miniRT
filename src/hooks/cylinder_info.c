/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:48:13 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/02 19:51:21 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#define CYLINDER_OFFSET 400

void	display_cylinder_info(t_scene *scene)
{
	char	*to_print;

	mlx_string_put(scene->mlx, scene->win, 10, CYLINDER_OFFSET + 20, 0xffffff,
		"Plane:");
	mlx_string_put(scene->mlx, scene->win, 10, CYLINDER_OFFSET + 40, 0xffffff,
		"x       y       z");
	to_print = get_coordinates(scene->selected->cylinder->center, 2);
	mlx_string_put(scene->mlx, scene->win, 10, CYLINDER_OFFSET + 60, 0xffffff,
		to_print);
	free(to_print);
	to_print = get_coordinates(scene->selected->cylinder->axis, 3);
	mlx_string_put(scene->mlx, scene->win, 10, CYLINDER_OFFSET + 80, 0xffffff,
		to_print);
	free(to_print);
	to_print = get_color_in_hex_string(scene->selected->cylinder->color);
	mlx_string_put(scene->mlx, scene->win, 10, CYLINDER_OFFSET + 100,
		rgb2int(scene->selected->cylinder->color),
		to_print);
	free(to_print);
}
