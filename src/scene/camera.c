/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:23:50 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 16:23:50 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera    *new_camera(t_vector *origin, t_vector *direction, float fov)
{
    t_camera *camera;

    camera = (t_camera *) malloc(sizeof(t_camera));
    if (!camera)
        handle_error(MEMORY_ERROR);
    camera->origin = origin;
    camera->direction = direction;
    camera->fov = fov;
    return (camera);
}