/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:43:44 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 11:43:48 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_ambient_light	*new_ambient_light(t_color *color, float lighting)
{
	t_ambient_light	*light;

	if (!color)
		return (NULL);
	light = (t_ambient_light *)malloc(sizeof(t_ambient_light));
	if (!light)
		return (NULL);
	light->color = color;
	light->lighting = lighting;
	return (light);
}

void	free_ambient_light(t_ambient_light *light)
{
	if (!light)
		return ;
	if (light->color)
		free_color(light->color);
	free(light);
}

t_light	*new_light(t_vector *origin, float brightness, t_color *color)
{
	t_light	*light;

	if (!color)
		return (NULL);
	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->origin = origin;
	light->brightness = brightness;
	light->color = color;
	return (light);
}

void	free_light(t_light *light)
{
	if (!light)
		return ;
	if (light->origin)
		free_vector(light->origin);
	if (light->color)
		free_color(light->color);
	free(light);
}
