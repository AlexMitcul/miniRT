/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:47:05 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/06 19:21:29 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_scene	*new_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *) ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->window_data = (t_window_data *) ft_calloc(1, sizeof(t_window_data));
	if (!scene->window_data)
		return (free_scene(scene), NULL);
	scene->width = CANVAS_WIDTH;
	scene->height = CANVAS_HEIGHT;
	scene->background_color = new_color(0, 0, 0);
	return (scene);
}

void free_mlx_data(t_scene *scene)
{
	mlx_destroy_window(scene->mlx, scene->win);
	if (scene->window_data)
	{
		mlx_destroy_image(scene->mlx, scene->window_data->img);
		free(scene->window_data);
	}
	mlx_destroy_display(scene->mlx);
	free(scene->mlx);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->light)
		free_light(scene->light);
	if (scene->ambient_light)
		free_ambient_light(scene->ambient_light);
	if (scene->camera)
		free_camera(scene->camera);
	free_sphere_list(scene->spheres);
	free_plane_list(scene->planes);
	free_cylinder_list(scene->cylinders);
	free_color(scene->background_color);
	free_mlx_data(scene);
	free(scene);
}
