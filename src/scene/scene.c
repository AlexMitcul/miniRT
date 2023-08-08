/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:47:05 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/08 17:53:06 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_scene	*new_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *) ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->width = CANVAS_WIDTH;
	scene->height = CANVAS_HEIGHT;
	scene->background_color = new_color(0, 0, 0);
	scene->selected_type = 0;
	scene->selected = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	return (scene);
}

void	free_mlx_data(t_scene *scene)
{
	if (!scene->mlx)
		return ;
	mlx_destroy_window(scene->mlx, scene->win);
	if (scene->window_data)
	{
		mlx_destroy_image(scene->mlx, scene->window_data->img);
		free(scene->window_data);
	}
	mlx_destroy_display(scene->mlx);
	free(scene->mlx);
}

void	free_menu(t_scene *scene)
{
	if (!scene->menu)
		return ;
	if (scene->menu->img)
		mlx_destroy_image(scene->mlx, scene->menu->img);
	free(scene->menu);
	scene->menu = NULL;
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
	free(scene->selected);
	free_mlx_data(scene);
	free(scene);
}
