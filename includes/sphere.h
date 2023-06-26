/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:08:26 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 16:08:26 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SPHERE_H
#define SPHERE_H

#include "minirt.h"
#include "scene.h"

typedef struct s_sphere
{
    t_vector *center;
    float radius;
    t_color *color;
    struct s_sphere *next;
} t_sphere;

t_sphere    *new_sphere(t_vector *center, float radius, t_color *color);
void        sphere_add_to_scene(t_scene *scene, t_sphere *sphere);

#endif