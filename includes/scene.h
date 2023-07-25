/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:27:17 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/25 12:37:06 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

typedef struct s_camera			t_camera;
typedef struct s_sphere			t_sphere;
typedef struct s_plane			t_plane;
typedef struct s_cylinder		t_cylinder;
typedef struct s_ambient_light	t_ambient_light;
typedef struct s_light			t_light;

typedef struct s_window_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_window_data;

typedef struct s_scene
{
	void			*mlx;
	void			*win;
	t_window_data	*window_data;
	t_camera		*camera;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
	t_light			*light;
	t_ambient_light	*ambient_light;
	float			width;
	float			height;
}	t_scene;

t_scene	*new_scene(void);
void	free_scene(t_scene *scene);

#endif
