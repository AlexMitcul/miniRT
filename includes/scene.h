/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:27:17 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/03 14:17:49 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

# define CANVAS_WIDTH	1920
# define CANVAS_HEIGHT	1080
# define CANVAS_WIDTH	1920
# define CANVAS_HEIGHT	1080
# define DISTANCE_TO_VIEWPORT 1

typedef struct s_camera			t_camera;
typedef struct s_sphere			t_sphere;
typedef struct s_plane			t_plane;
typedef struct s_cylinder		t_cylinder;
typedef struct s_ambient_light	t_ambient_light;
typedef struct s_light			t_light;

typedef struct s_window_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_window_data;

typedef enum e_selected_type
{
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
}	t_selected_type;

typedef struct s_menu
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}	t_menu;

typedef struct s_selected
{
	int			sphere_index;
	t_sphere	*sphere;
	int			plane_index;
	t_plane		*plane;
	int			cylinder_index;
	t_cylinder	*cylinder;
}	t_selected;

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

	t_selected		*selected;
	char			selected_type;
	int				selected_sphere;
	bool			is_menu_open;
	t_menu			*menu;
}	t_scene;

t_scene	*new_scene(void);
void	free_scene(t_scene *scene);
void	free_menu(t_scene *scene);

#endif
