/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:51:47 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/29 00:49:11 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	setup_scene(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(
			scene->mlx, scene->width, scene->height, "miniRT");
	scene->window_data->img = mlx_new_image(scene->mlx, scene->width,
			scene->height);
	scene->window_data->addr = mlx_get_data_addr(scene->window_data->img,
			&scene->window_data->bits_per_pixel,
			&scene->window_data->line_length,
			&scene->window_data->endian);
	scene->camera->fov *= PI / 180;
	scene->camera->aspect_ratio = (float)CANVAS_HEIGHT / (float)CANVAS_WIDTH;
	// scene->camera->viewport_width = 2;
	// scene->camera->viewport_height = scene->camera->viewport_width * scene->camera->aspect_ratio;
	// scene->focal_length = 1;
	// scene->focal_length = 1 / tan(scene->camera->fov / 2);
	scene->focal_length = DISTANCE_TO_VIEWPORT;
	scene->camera->viewport_width = 2 * (float)atan(scene->camera->fov / 2 * scene->focal_length);
	scene->camera->viewport_height = scene->camera->viewport_width * scene->camera->aspect_ratio;
	// scene->camera->viewport_width = scene->camera->viewport_width * scene->camera->aspect_ratio;
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	//	test();
	if (argc != 2)
		handle_error(ARGUMENTS_COUNT_ERROR, NULL);
	scene = parser(argv[1]);
	if (!scene)
		return (free_scene(scene), 1);
	setup_scene(scene);
	mlx_hook(scene->win, 2, 1L << 0, close_win, scene);
	mlx_hook(scene->win, 17, 0, close_win_with_cross, scene);
	render(scene);
	mlx_loop(scene->mlx);
	free_scene(scene);
	return (0);
}
