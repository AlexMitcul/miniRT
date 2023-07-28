/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:43:36 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/27 01:08:24 by amenses-         ###   ########.fr       */
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
/*
	119	w
	115	s
	97	a
	100	d

	113	q
	101	e
*/
static void	move_camera(t_scene *scene, int keycode)
{
	/*
		I'm not sure about right orientation, but for template is ok
	*/
	if (keycode == 119)
		scene->camera->origin->z += 0.01;
	else if (keycode == 115)
		scene->camera->origin->z -= 0.01;
	else if (keycode == 97)
		scene->camera->origin->x += 0.01;
	else if (keycode == 100)
		scene->camera->origin->x -= 0.1;
	// printf("camera origin: %f %f %f\n", scene->camera->origin->x, scene->camera->origin->y, scene->camera->origin->z);
	new_image(scene);
	render(scene);
}

int	close_win(int keycode, t_scene *scene)
{
	// printf("keycode: %d\n", keycode);
	if (keycode == 65307)
		close_app(scene);
	else
		move_camera(scene, keycode);
	/* debug only */
	if (keycode == 119)
		printf("w\n");
	else if (keycode == 115)
		printf("s\n");
	else if (keycode == 97)
		printf("a\n");
	else if (keycode == 100)
		printf("d\n");
	else if (keycode == 113)
		printf("q\n");
	else if (keycode == 101)
		printf("e\n");
	return (0);
}

int	close_win_with_cross(void *data)
{
	close_app((t_scene *)data);
	return (0);
}
