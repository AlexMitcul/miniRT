/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:27:17 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 16:27:17 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SCENE_H_
# define SCENE_H_

# include "minirt.h"

typedef struct s_scene
{
    t_camera *camera;
    t_sphere *spheres;
    t_plane *planes;
    t_cylinder  *cylinders;
	t_ambient_light *ambient_light;
    float width;
    float height;
} t_scene;

t_scene *new_scene(float, float);
void	free_scene(t_scene *);

#endif