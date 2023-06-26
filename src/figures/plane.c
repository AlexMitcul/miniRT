/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:44:32 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/26 09:44:35 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_plane    *new_plane(t_vector *origin, t_vector *direction, t_color *color)
{
    t_plane *plane;

    plane = (t_plane *) malloc(sizeof(t_plane));
    if (!plane)
        handle_error(MEMORY_ERROR, NULL);
    plane->origin = origin;
    plane->color = color;
    plane->direction = direction;
    plane->next = NULL;
    return (plane);
}

void    plane_add_to_scene(t_scene *scene, t_plane *plane)
{
    if (scene->planes)
        plane->next = scene->planes;
    scene->planes = plane;
}