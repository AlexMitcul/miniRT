/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:51:47 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/08 20:43:07 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	set_camera(t_camera *camera)
{
	t_vector	*up_guide;

	up_guide = new_vector(0.0f, 1.0f, 0.0f);
	camera->fov *= (float)PI / 180.0f / 2.0f;
	camera->aspect_ratio = (float)CANVAS_HEIGHT / (float)CANVAS_WIDTH;
	camera->viewport_width = (float)tan(camera->fov) * \
		(float)DISTANCE_TO_VIEWPORT;
	camera->viewport_height = camera->viewport_width * camera->aspect_ratio;
	camera->f = vec_dup(camera->direction);
	vec_normalize(camera->f);
	if (vec_product(camera->f, up_guide) == 1.0f)
		up_guide->x -= 0.1f;
	camera->u = vec_cross_product(up_guide, camera->f);
	vec_normalize(camera->u);
	camera->v = vec_cross_product(camera->f, camera->u);
	free(up_guide);
}

void	setup_scene(t_scene *scene)
{
	scene->window_data = malloc(sizeof(t_window_data));
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

	if (argc != 2)
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}
	scene = parser(argv[1]);
	if (!scene || !scene->camera || !scene->ambient_light || !scene->light)
	{
		printf("Error\n");
		return (free_scene(scene), EXIT_FAILURE);
	}
	setup_scene(scene);
	mlx_hook(scene->win, 2, 1L << 0, close_win, scene);
	mlx_hook(scene->win, 17, 0, close_win_with_cross, scene);
	render(scene);
	mlx_loop(scene->mlx);
	free_scene(scene);
	return (0);
}
