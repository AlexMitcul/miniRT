/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:44:32 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/06 18:24:55 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_plane	*new_plane(t_vector *origin, t_vector *direction, t_color *color)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		handle_error(MEMORY_ERROR, NULL);
	plane->origin = origin;
	plane->color = color;
	plane->direction = direction;
	plane->is_cylinder_cap = 0;
	plane->next = NULL;
	return (plane);
}

void	plane_add_to_scene(t_scene *scene, t_plane *plane)
{
	if (scene->planes)
		plane->next = scene->planes;
	scene->planes = plane;
}

void	free_plane(t_plane *plane)
{
	if (!plane)
		return ;
	if (plane->origin)
		free_vector(plane->origin);
	if (plane->direction)
		free_vector(plane->direction);
	if (plane->color)
		free_color(plane->color);
	free(plane);
}

void	free_plane_list(t_plane *head)
{
	t_plane	*current;
	t_plane	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_plane(current);
		current = next;
	}
}
