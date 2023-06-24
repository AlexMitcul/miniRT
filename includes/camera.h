/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:20:52 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 16:20:52 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SCENE_H
#define SCENE_H

# include "minirt.h"

typedef struct s_camera
{
    t_vector *origin;
    t_vector *direction;
    float fov;
} t_camera;

t_camera    *new_camera(t_vector *origin, t_vector *direction, float fov);

#endif