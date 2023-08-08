/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:08:34 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/08 18:10:17 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_sphere	*new_sphere(t_vector *center, float radius, t_color *color)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = center;
	sphere->radius = radius;
	sphere->color = color;
	sphere->next = NULL;
	sphere->prev = NULL;
	return (sphere);
}

void	sphere_add_to_scene(t_scene *scene, t_sphere *sphere)
{
	if (scene->spheres)
	{
		scene->spheres->prev = sphere;
		sphere->next = scene->spheres;
	}
	scene->spheres = sphere;
}

void	free_sphere(t_sphere *sphere)
{
	if (!sphere)
		return ;
	if (sphere->center)
		free(sphere->center);
	if (sphere->color)
		free(sphere->color);
	free(sphere);
}

void	free_sphere_list(t_sphere *head)
{
	t_sphere	*current;
	t_sphere	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_sphere(current);
		current = next;
	}
}
