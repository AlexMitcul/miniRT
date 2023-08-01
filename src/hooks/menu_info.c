/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:13:29 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/01 18:36:58 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	display_info(t_scene *scene)
{
	mlx_string_put(scene->mlx, scene->win, 10, 20, 0xffff00,
		" press ESC:           exit");
	mlx_string_put(scene->mlx, scene->win, 10, 80, 0xffff00,
		" left mouse button:   rotation");
	mlx_string_put(scene->mlx, scene->win, 10, 100, 0xffff00,
		" right mouse button:  translation");
	mlx_string_put(scene->mlx, scene->win, 10, 120, 0xffff00,
		" scroll up/down:      zoom in/out");
	mlx_string_put(scene->mlx, scene->win, 10, 140, 0xffff00,
		" press C:             change color mode");
	mlx_string_put(scene->mlx, scene->win, 10, 160, 0xffff00,
		" press H:             help");
	mlx_string_put(scene->mlx, scene->win, 10, 180, 0xffff00,
		" press I:             isometric mode");
	mlx_string_put(scene->mlx, scene->win, 10, 200, 0xffff00,
		" press P:             perspective mode");
	mlx_string_put(scene->mlx, scene->win, 10, 220, 0xffff00,
		" press S:             depth-shade mode");
}

/*
Camera:
x	y	z
0.0	0.0	0.0
0.00 0.01 1.02

Light:
0x00FF00
x	y	z
0.0	0.0	0.0

Plane
0x00FF00
x	y	z
0.0	0.0	0.0
0.00 0.01 1.02

Sphere
0x00FF00
x	y	z
0.0	0.0	0.0

Cylinder
0x00FF00
x	y	z
0.0	0.0	0.0
0.00 0.01 1.02
*/
