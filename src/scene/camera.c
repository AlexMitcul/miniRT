/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:23:50 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/08 20:55:21 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_camera	*new_camera(t_vector *origin, t_vector *direction, float fov)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof (t_camera));
	if (!camera)
		return (NULL);
	camera->origin = origin;
	camera->direction = direction;
	camera->fov = fov;
	return (camera);
}

void	free_camera(t_camera *camera)
{
	if (!camera)
		return ;
	if (camera->origin)
		free_vector(camera->origin);
	if (camera->direction)
		free_vector(camera->direction);
	if (camera->f)
		free_vector(camera->f);
	if (camera->u)
		free_vector(camera->u);
	if (camera->v)
		free_vector(camera->v);
	free(camera);
	camera = NULL;
}
