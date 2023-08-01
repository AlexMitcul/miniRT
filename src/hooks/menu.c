/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:58:31 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/01 16:50:31 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#define MENU_WIDTH 200
#define MENU_HEIGHT 1080

void	menu_pixel_put(t_menu *img, int x, int y, t_color *color)
{
	char	*pxl;

	pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pxl = rgb2int(color);
}

void	render_menu(t_scene *scene)
{
	scene->menu = (t_menu *) ft_calloc(1, sizeof(t_menu));
	scene->menu->img = mlx_new_image(scene->mlx, MENU_WIDTH, MENU_HEIGHT);
	scene->menu->addr = mlx_get_data_addr(scene->menu->img,
			&scene->menu->bits_per_pixel,
			&scene->menu->line_length,
			&scene->menu->endian);
	t_color *color = new_color(150, 150, 150);
	if (!scene->menu->img)
		printf("there is no image");
	for (int i = 0; i < MENU_HEIGHT; i++)
		for (int j = 0; j < MENU_WIDTH; j++)
			menu_pixel_put(scene->menu, i, j, color);
	free_color(color);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->menu->img, 0, 0);
}

/*
void	display_menu(t_scene *scene)
{
	mlx_string_put(scene->mlx, scene->win, 10, 20, 0xffff00, \
		"+ + + + + + + + + + + + + + + + + + + + + +");
	mlx_string_put(scene->mlx, scene->win, 10, 40, 0xffff00, \
		"+                HELP                     +");
	mlx_string_put(scene->mlx, scene->win, 10, 60, 0xffff00, \
		"+ + + + + + + + + + + + + + + + + + + + + +");
	mlx_string_put(scene->mlx, scene->win, 10, 80, 0xffff00, \
		" left mouse button:   rotation");
	mlx_string_put(scene->mlx, scene->win, 10, 100, 0xffff00, \
		" right mouse button:  translation");
	mlx_string_put(scene->mlx, scene->win, 10, 120, 0xffff00, \
		" scroll up/down:      zoom in/out");
	mlx_string_put(scene->mlx, scene->win, 10, 140, 0xffff00, \
		" press C:             change color mode");
	mlx_string_put(scene->mlx, scene->win, 10, 160, 0xffff00, \
		" press H:             help");
	mlx_string_put(scene->mlx, scene->win, 10, 180, 0xffff00, \
		" press I:             isometric mode");
	mlx_string_put(scene->mlx, scene->win, 10, 200, 0xffff00, \
		" press P:             perspective mode");
	mlx_string_put(scene->mlx, scene->win, 10, 220, 0xffff00, \
		" press S:             depth-shade mode");
}
*/
