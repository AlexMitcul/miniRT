/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:48:00 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/06 20:39:26 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	new_image(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->window_data->img);
	scene->window_data->img = mlx_new_image(scene->mlx, \
	CANVAS_WIDTH, CANVAS_HEIGHT);
	if (!scene->window_data->img)
		return (1);
	scene->window_data->addr = mlx_get_data_addr(scene->window_data->img, \
		&scene->window_data->bits_per_pixel, \
		&scene->window_data->line_length, &scene->window_data->endian);
	return (0);
}

static void	pixel_put(t_window_data *img, int x, int y, t_color *color)
{
	char	*pxl;

	pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pxl = rgb2int(color);
}

void	render(t_scene *scene)
{
	int			x;
	int			y;
	t_render	*render;

	set_cylinder_caps(scene->cylinders);
	y = -1;
	while (++y < CANVAS_HEIGHT)
	{
		x = -1;
		while (++x < CANVAS_WIDTH)
		{
			render = new_render(scene, x, y);
			render->color = trace_ray(scene, render->ray);
			pixel_put(scene->window_data, x, y, render->color);
			free_render(render);
		}
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->window_data->img, \
		0, 0);
}
