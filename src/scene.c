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

#include "../includes/minirt.h"

t_scene *new_scene(float width, float height)
{
    t_scene *scene;

    scene = (t_scene *) malloc(sizeof(t_scene));
    scene->width = width;
    scene->height = height;
    scene->cameras = NULL;
    scene->spheres = NULL;
    return (scene);
}