/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:51:47 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/01 03:25:48 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	set_camera(t_camera *camera)
{
	t_vector	*up_guide;

	up_guide = new_vector(0, 1, 0);
	camera->fov *= (float)PI / 180 / 2;
	// camera->fov *= (float)PI / 180;
	camera->aspect_ratio = (float)CANVAS_HEIGHT / (float)CANVAS_WIDTH;
	camera->viewport_width = (float)tan(camera->fov) * (float)DISTANCE_TO_VIEWPORT;
	// scene->camera->viewport_width = 2 * (float)atan(scene->camera->fov / 2) * DISTANCE_TO_VIEWPORT;
	camera->viewport_height = camera->viewport_width * camera->aspect_ratio;
	camera->f = vec_dup(camera->direction); // free
	// camera->f = vec_substract(camera->direction, camera->origin); // ?
	vec_normalize(camera->f);
	camera->u = vec_cross_product(camera->f, up_guide);
	vec_normalize(camera->u);
	camera->v = vec_cross_product(camera->u, camera->f);
	free(up_guide);
	// printf("camera->fov: %f\n", camera->fov);
	// printf("camera->aspect_ratio: %f\n", camera->aspect_ratio);
	// printf("camera->viewport_width: %f\n", camera->viewport_width);
	// printf("camera->viewport_height: %f\n", camera->viewport_height);
	// printf("camera->f: %f, %f, %f\n", camera->f->x, camera->f->y, camera->f->z);
	// printf("camera->u: %f, %f, %f\n", camera->u->x, camera->u->y, camera->u->z);
	// printf("camera->v: %f, %f, %f\n", camera->v->x, camera->v->y, camera->v->z);
}

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
	set_camera(scene->camera);
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
