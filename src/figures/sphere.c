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

t_sphere    *new_sphere(t_vector *center, float radius)
{
    t_sphere    *sphere;

    sphere = (t_sphere *) malloc(sizeof(t_sphere));
    if (!sphere)
        handle_error(MEMORY_ERROR, NULL);
    sphere->center = center;
    sphere->radius = radius;
    return (sphere);
}