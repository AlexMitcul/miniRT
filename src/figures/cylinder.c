/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:53:50 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/08 18:10:33 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_cylinder	*new_cylinder(t_vector *center, t_vector *axis, float num_data[2],
	t_color *color)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->center = center;
	cylinder->axis = axis;
	cylinder->radius = num_data[0];
	cylinder->height = num_data[1];
	cylinder->color = color;
	cylinder->cap[0] = NULL;
	cylinder->cap[1] = NULL;
	cylinder->next = NULL;
	cylinder->prev = NULL;
	return (cylinder);
}

void	cylinder_add_to_scene(t_scene *scene, t_cylinder *cylinder)
{
	if (scene->cylinders)
	{
		scene->cylinders->prev = cylinder;
		cylinder->next = scene->cylinders;
	}
	scene->cylinders = cylinder;
}

void	free_cylinder(t_cylinder *cylinder)
{
	if (!cylinder)
		return ;
	if (cylinder->center)
		free_vector(cylinder->center);
	if (cylinder->axis)
		free_vector(cylinder->axis);
	if (cylinder->color)
		free_color(cylinder->color);
	if (cylinder->cap[0])
		free_plane(cylinder->cap[0]);
	if (cylinder->cap[1])
		free_plane(cylinder->cap[1]);
	free(cylinder);
}

void	free_cylinder_list(t_cylinder *head)
{
	t_cylinder	*current;
	t_cylinder	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_cylinder(current);
		current = next;
	}
}
