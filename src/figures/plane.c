/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:09:18 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/08 18:10:26 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_plane	*new_plane(t_vector *origin, t_vector *direction, t_color *color)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->origin = origin;
	plane->color = color;
	plane->direction = direction;
	plane->is_cylinder_cap = 0;
	plane->next = NULL;
	plane->prev = NULL;
	return (plane);
}

void	plane_add_to_scene(t_scene *scene, t_plane *plane)
{
	if (scene->planes)
	{
		scene->planes->prev = plane;
		plane->next = scene->planes;
	}
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
