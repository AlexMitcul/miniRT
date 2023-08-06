/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:54:52 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/06 20:39:45 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_vector	*get_canvas_point(int x, int y)
{
	float	cx;
	float	cy;

	cx = 2.0f * ((float)x) / (float)CANVAS_WIDTH - 1.0f;
	cy = 2.0f * ((float)y) / (float)CANVAS_HEIGHT - 1.0f;
	cy *= -1.0f;
	return (new_vector(cx, cy, 0.0f));
}

t_vector	*canvas_to_viewport(t_scene *scene, t_vector *canvas_point)
{
	t_vector	*v;

	v = new_vector(0.0f, 0.0f, 0.0f);
	v->x = canvas_point->x * scene->camera->viewport_width;
	v->y = canvas_point->y * scene->camera->viewport_height;
	v->z = DISTANCE_TO_VIEWPORT;
	return (v);
}

t_render	*new_render(t_scene *scene, int x, int y)
{
	t_render	*render;

	render = ft_calloc(1, sizeof(t_render));
	render->canvas_point = get_canvas_point(x, y);
	render->viewport_point = canvas_to_viewport(scene, render->canvas_point);
	render->ray = camera_ray(scene->camera, render->viewport_point);
	vec_normalize(render->ray->d);
	return (render);
}

void	free_render(t_render *render)
{
	if (!render)
		return ;
	if (render->canvas_point)
		free_vector(render->canvas_point);
	if (render->viewport_point)
		free_vector(render->viewport_point);
	if (render->ray)
		free_ray(render->ray);
	if (render->color)
		free_color(render->color);
	free(render);
}
