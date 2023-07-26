/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:20:52 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/26 13:39:21 by amenses-         ###   ########.fr       */
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
	float		viewport_width;
	float		viewport_height;
	float		aspect_ratio;
}				t_camera;

t_camera		*new_camera(t_vector *origin, t_vector *direction, float fov);
void			free_camera(t_camera *camera);

#endif
