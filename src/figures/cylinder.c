/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:53:50 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/05 00:31:35 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_cylinder	*new_cylinder(t_vector *center, t_vector *axis, float radius,
		float height, t_color *color)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->center = center;
	cylinder->axis = axis;
	cylinder->radius = radius;
	cylinder->height = height;
	cylinder->color = color;
	ft_bzero(cylinder->c, sizeof(t_vector *) * 2);
	cylinder->next = NULL;
	return (cylinder);
}

void	cylinder_add_to_scene(t_scene *scene, t_cylinder *cylinder)
{
	if (scene->cylinders)
		cylinder->next = scene->cylinders;
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
	if (cylinder->c[0])
		free_vector(cylinder->c[0]);
	if (cylinder->c[1])
		free_vector(cylinder->c[1]);
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
