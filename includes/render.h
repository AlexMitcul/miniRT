/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:30:16 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/04 02:26:59 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

# define PI 		3.14159265358979323846264338
# define EPSYLON	0.001

typedef enum e_object_type
{
	PLANE,
	SPHERE,
	CYLINDER,
}	e_object_type;

typedef struct s_intersection
{
	t_vector				*p;
	t_vector				*n;
	float					t;
	int						type;
	t_color					*color;
	t_sphere				*sp;
	t_plane					*pl;
	t_cylinder				*cyl;
}   t_intersection;

typedef struct s_ray
{
	t_vector		*o;
	t_vector		*d;
	t_intersection	*intersection;
}   t_ray;

void		render(t_scene *scene);
void		render_sphere(t_scene *scene);
int			new_image(t_scene *scene);

t_ray		*new_ray(t_vector *point, t_vector *direction);
// t_ray		*new_lightray(t_vector *origin, t_vector *point);
// t_ray	*light_ray(t_vector *origin, t_vector *point);
// t_ray		*new_ray(t_vector *origin, t_vector *point);
// t_ray	*new_ray(t_vector *origin, t_vector *point, t_camera *camera);
t_ray		*camera_ray(t_camera *camera, t_vector *point);
t_ray		*scene_ray(t_vector *origin, t_vector *point);
t_vector	*ray_point(t_ray *ray, float t);
t_vector	*vec_point(t_vector *origin, t_vector *directions, float t);
void		free_ray(t_ray *ray);

void	setup_scene(t_scene *scene);

#endif
