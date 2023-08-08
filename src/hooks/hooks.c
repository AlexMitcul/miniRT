/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 08:01:13 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/08 08:03:19 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	close_app(t_scene *scene)
{
	if (!scene)
		return ;
	free_scene(scene);
	exit(0);
}

t_vector	*get_selected_origin(t_scene *scene)
{
	if (scene->selected_type == CAMERA)
		return (scene->camera->origin);
	else if (scene->selected_type == LIGHT)
		return (scene->light->origin);
	else if (scene->selected_type == SPHERE)
		return (scene->selected->sphere->center);
	else if (scene->selected_type == PLANE)
		return (scene->selected->plane->origin);
	else if (scene->selected_type == CYLINDER)
		return (scene->selected->cylinder->center);
	return (scene->camera->origin);
}

void	move_object(t_vector *vector, int keycode)
{
	if (keycode == PLUS)
		update(vector, Z, -0.1);
	else if (keycode == MINUS)
		update(vector, Z, 0.1);
	else if (keycode == RIGHT)
		update(vector, X, 0.1);
	else if (keycode == LEFT)
		update(vector, X, -0.1);
	else if (keycode == UP)
		update(vector, Y, -0.1);
	else if (keycode == DOWN)
		update(vector, Y, 0.1);
}

int	close_win_with_cross(void *data)
{
	close_app((t_scene *)data);
	return (0);
}

int	close_win(int keycode, t_scene *scene)
{
	if (keycode == ESC)
		close_app(scene);
	else
		move_object(get_selected_origin(scene), keycode);
	render(scene);
	return (0);
}
