/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:58:31 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/02 19:46:39 by amitcul          ###   ########.fr       */
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

bool	is_in_selected_range(size_t i, t_selected_type selected_type)
{
	if (selected_type == 0)
		return (i >= 0 && i < 100);
	else if (selected_type == 1)
		return (i >= 100 && i < 200);
	else if (selected_type == 2)
		return (i >= 200 && i < 300);
	else if (selected_type == 3)
		return (i >= 300 && i < 400);
	else if (selected_type == 4)
		return (i >= 400 && i < 500);
	return (false);
}

void	fill_bg(t_scene *scene)
{
	t_color	*bg;
	t_color	*selected;
	size_t	i;
	size_t	j;

	bg = new_color(30, 30, 30);
	selected = new_color(40, 40, 40);
	i = 0;
	while (i < MENU_HEIGHT)
	{
		j = 0;
		while (j < MENU_WIDTH)
		{
			if (is_in_selected_range(i, scene->selected_type))
				menu_pixel_put(scene->menu, j, i, selected);
			else
				menu_pixel_put(scene->menu, j, i, bg);
			j++;
		}
		i++;
	}
	free_color(bg);
	free_color(selected);
}

void	render_menu(t_scene *scene)
{
	scene->menu = (t_menu *) ft_calloc(1, sizeof(t_menu));
	scene->menu->img = mlx_new_image(scene->mlx, MENU_WIDTH, MENU_HEIGHT);
	scene->menu->addr = mlx_get_data_addr(scene->menu->img,
			&scene->menu->bits_per_pixel,
			&scene->menu->line_length,
			&scene->menu->endian);
	fill_bg(scene);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->menu->img, 0, 0);
	display_info(scene);
	// display_minimap(scene);
}
