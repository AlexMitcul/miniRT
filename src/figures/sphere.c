/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:08:34 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 16:08:34 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_sphere    *new_sphere(t_vector *center, float radius, t_color *color)
{
    t_sphere    *sphere;

    sphere = (t_sphere *) malloc(sizeof(t_sphere));
    if (!sphere)
        handle_error(MEMORY_ERROR, NULL);
    sphere->center = center;
    sphere->radius = radius;
    sphere->color = color;
    sphere->next = NULL;
    return (sphere);
}

void    sphere_add_to_scene(t_scene *scene, t_sphere *sphere)
{
    if (scene->spheres)
        sphere->next = scene->spheres;
    scene->spheres = sphere;
}