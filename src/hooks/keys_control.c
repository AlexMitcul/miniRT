/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:43:36 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/02 20:11:19 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	close_app(t_scene *scene)
{
	if (!scene)
		return ;
	free_scene(scene);
	exit(0);
}
/*
	119	w
	115	s
	97	a
	100	d

	113	q
	101	e

	65293 enter
*/
static void	move_camera(t_scene *scene, int keycode)
{
	/*
		I'm not sure about right orientation, but for template is ok
	*/
	if (keycode == 119)
		scene->camera->origin->z -= 1;
	else if (keycode == 115)
		scene->camera->origin->z += 0.1;
	else if (keycode == 97)
		scene->camera->origin->x += 0.1;
	else if (keycode == 100)
		scene->camera->origin->x -= 0.1;
	printf("camera origin: %f %f %f\n", scene->camera->origin->x, scene->camera->origin->y, scene->camera->origin->z);
	new_image(scene);
	render(scene);
}

void	update_selected_type(t_scene *scene, int direction)
{
	if (scene->is_menu_open)
	{
		scene->selected_type += direction;
		if (scene->selected_type < 0)
			scene->selected_type = 4;
		else if (scene->selected_type > 4)
			scene->selected_type = 0;
	}
	render(scene);
}

void	update_lists(t_scene *scene)
{
	(void)scene;
	scene->selected->plane = scene->selected->plane->next;
}

void	update_selected_element(t_scene *scene, int direction)
{
	if (scene->selected_type == 2)
		scene->selected->cylinder_index += direction;
	else if (scene->selected_type == 3)
		scene->selected->plane_index += direction;
	else if (scene->selected_type == 4)
		scene->selected->cylinder += direction;
	update_lists(scene);
	render(scene);
}

int	close_win(int keycode, t_scene *scene)
{
	printf("keycode: %d\n", keycode);
	if (scene->is_menu_open)
		printf("selected type: %d\n", scene->selected_type);
	if (keycode == 65307)
		close_app(scene);
	if (keycode == 65293)
	{
		scene->is_menu_open = !scene->is_menu_open;
		new_image(scene);
		render(scene);
	}
	else if (keycode == 65362)
		update_selected_type(scene, -1);
	else if (keycode == 65364)
		update_selected_type(scene, 1);
	else if (keycode == 65363)
		update_selected_element(scene, 1);
	else if (keycode == 65361)
		update_selected_element(scene, -1);
	else
		move_camera(scene, keycode);
	return (0);
}

int	close_win_with_cross(void *data)
{
	close_app((t_scene *)data);
	return (0);
}
