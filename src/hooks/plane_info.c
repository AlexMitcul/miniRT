/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:41:29 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/02 19:47:53 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#define PLANE_OFFSET 200

void	display_plane_info(t_scene *scene)
{
	char	*to_print;

	mlx_string_put(scene->mlx, scene->win, 10, PLANE_OFFSET + 20, 0xffffff,
		"Plane:");
	mlx_string_put(scene->mlx, scene->win, 10, PLANE_OFFSET + 40, 0xffffff,
		"x       y       z");
	to_print = get_coordinates(scene->planes->origin, 2);
	mlx_string_put(scene->mlx, scene->win, 10, PLANE_OFFSET + 60, 0xffffff,
		to_print);
	free(to_print);
	to_print = get_coordinates(scene->planes->direction, 3);
	mlx_string_put(scene->mlx, scene->win, 10, PLANE_OFFSET + 80, 0xffffff,
		to_print);
	free(to_print);
	to_print = get_color_in_hex_string(scene->selected->plane->color);
	mlx_string_put(scene->mlx, scene->win, 10, PLANE_OFFSET + 100,
		rgb2int(scene->selected->plane->color),
		to_print);
	free(to_print);
}