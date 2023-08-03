/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:43:36 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/03 15:31:21 by amitcul          ###   ########.fr       */
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

static void	move_camera(t_scene *scene, int keycode)
{
	if (keycode == PLUS)
		scene->camera->origin->z -= 0.1;
	else if (keycode == MINUS)
		scene->camera->origin->z += 0.1;
	else if (keycode == RIGHT)
		scene->camera->origin->x += 0.1;
	else if (keycode == LEFT)
		scene->camera->origin->x -= 0.1;
	else if (keycode == UP)
		scene->camera->origin->y -= 0.1;
	else if (keycode == DOWN)
		scene->camera->origin->y += 0.1;
	// printf("camera origin: %f %f %f\n", scene->camera->origin->x, scene->camera->origin->y, scene->camera->origin->z);
	// new_image(scene);
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

void	update_selected_element(t_scene *scene, int direction)
{
	if (scene->selected_type == SPHERE && direction < 0 && scene->selected->sphere->prev)
		scene->selected->sphere = scene->selected->sphere->prev;
	else if (scene->selected_type == SPHERE && direction > 0 && scene->selected->sphere->next)
		scene->selected->sphere = scene->selected->sphere->next;
	else if (scene->selected_type == PLANE && direction < 0 && scene->selected->plane->prev)
		scene->selected->plane = scene->selected->plane->prev;
	else if (scene->selected_type == PLANE && direction > 0 && scene->selected->plane->next)
		scene->selected->plane = scene->selected->plane->next;
	else if (scene->selected_type == CYLINDER && direction < 0 && scene->selected->cylinder->prev)
		scene->selected->cylinder = scene->selected->cylinder->prev;
	else if (scene->selected_type == CYLINDER && direction > 0 && scene->selected->cylinder->next)
		scene->selected->cylinder = scene->selected->cylinder->next;
	render(scene);
}

int	close_win(int keycode, t_scene *scene)
{
	printf("key = %d\n", keycode);
	// (void)scene;
	// return 0;
	// printf("asdkasda;lsd\n");
	// printf("keycode: %d\n", keycode);
	// if (keycode == 65307)
	// 	close_app(scene);
	// if (keycode == 65438)
	// {
	// 	scene->is_menu_open = !scene->is_menu_open;
	// 	// new_image(scene);
	// 	render(scene);
	// }
	// else if (keycode == 65362)
	// 	update_selected_type(scene, -1);
	// else if (keycode == 65364)
	// 	update_selected_type(scene, 1);
	// else if (keycode == 65363)
	// 	update_selected_element(scene, 1);
	// else if (keycode == 65361)
	// 	update_selected_element(scene, -1);
	// else
	// 	move_camera(scene, keycode);
	return (0);
}

int	close_win_with_cross(void *data)
{
	close_app((t_scene *)data);
	return (0);
}
