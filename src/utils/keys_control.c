/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:43:36 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/07 20:14:00 by amitcul          ###   ########.fr       */
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

static void	move_camera(t_scene *scene, int keycode)
{
	if (keycode == 119)
		scene->camera->origin->z += 0.2;
	else if (keycode == 115)
		scene->camera->origin->z -= 0.2;
	else if (keycode == 97)
		scene->camera->origin->x -= 0.2;
	else if (keycode == 100)
		scene->camera->origin->x += 0.2;
	new_image(scene);
	render(scene);
}

int	close_win(int keycode, t_scene *scene)
{
	if (keycode == 65307)
		close_app(scene);
	else
		move_camera(scene, keycode);
	return (0);
}

int	close_win_with_cross(void *data)
{
	close_app((t_scene *)data);
	return (0);
}
