/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:47:05 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 16:47:05 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_scene *new_scene(float width, float height)
{
    t_scene *scene;

    scene = (t_scene *) malloc(sizeof(t_scene));
    scene->width = width;
    scene->height = height;
	scene->ambient_light = NULL;
    scene->light = NULL;
    scene->camera = NULL;
    scene->spheres = NULL;
    scene->planes = NULL;
    scene->cylinders = NULL;
    return (scene);
}

void free_scene(t_scene *scene)
{
	if (!scene)
		return ;
    if (scene->light)
        free_light(scene->light);
    if (scene->ambient_light)
        free_ambient_light(scene->ambient_light);
    if (scene->camera)
        free_camera(scene->camera);
    free_sphere_list(scene->spheres);
    free_plane_list(scene->planes);
    free_cylinder_list(scene->cylinders);
    free(scene);
}