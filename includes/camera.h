/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:20:52 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 10:48:55 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "minirt.h"

typedef struct s_camera
{
	t_vector	*origin;
	t_vector	*direction;
	float		fov;
}				t_camera;

t_camera		*new_camera(t_vector *origin, t_vector *direction, float fov);

void			free_camera(t_camera *camera);

#endif
