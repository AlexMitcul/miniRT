/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:27:17 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/30 02:29:20 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

# define CANVAS_WIDTH	400
# define CANVAS_HEIGHT	200
# define DISTANCE_TO_VIEWPORT 1

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
	float			aspect_ratio;
	float			viewport_width;
	float			viewport_height;
	t_color			*background_color;
}	t_scene;

t_scene	*new_scene(void);
void	free_scene(t_scene *scene);

#endif
