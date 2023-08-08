/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:58:31 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/07 20:23:06 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#define MENU_WIDTH 250
#define MENU_HEIGHT 1080

void	menu_pixel_put(t_menu *img, int x, int y, t_color *color)
{
	char	*pxl;

	pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	(void)color;
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
	mlx_put_image_to_window(scene->mlx, scene->win, scene->menu->img, 0, 0);
}
