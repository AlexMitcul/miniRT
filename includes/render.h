/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:30:16 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/08 08:04:09 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

# define PI 3.14159265358979323846264338
# define EPSYLON 0.001

typedef enum e_object_type
{
	TYPE_NONE,
	TYPE_PLANE,
	TYPE_SPHERE,
	TYPE_CYLINDER,
}	t_object_type;

typedef struct s_intersection
{
	t_vector		*p;
	t_vector		*n;
	float			t[4];
	float			t0;
	int				type;
	t_color			*color;
	t_sphere		*sp;
	t_plane			*pl;
	t_cylinder		*cy;
}					t_intersection;

typedef struct s_ray
{
	t_vector		*o;
	t_vector		*d;
	t_intersection	*intersection;
	float			t_min;
	float			t_max;
}					t_ray;

typedef struct s_render
{
	t_vector		*viewport_point;
	t_vector		*canvas_point;
	t_ray			*ray;
	t_color			*color;
}					t_render;

typedef struct s_quadratic
{
	float			a;
	float			b;
	float			c;
	float			d;
}					t_quadratic;

/* interceptor.c */
int					intersect_object(void *object, t_ray *ray, int type);

/* interceptor_hit_points.c */
int					hit_sphere(t_sphere *sphere, t_ray *ray);
int					hit_plane(t_plane *plane, t_ray *ray);
int					hit_cylinder(t_cylinder *cy, t_ray *ray);
void				set_cylinder_caps(t_cylinder *cylinders);

/* math_utils.c */
float				f_abs(float a);

/* picasso.c */
int					new_image(t_scene *scene);
void				render(t_scene *scene);

/* picasso_utils.c */
t_vector			*canvas_to_viewport(t_scene *scene, t_vector *canvas_point);
t_render			*new_render(t_scene *scene, int x, int y);
void				free_render(t_render *render);

/* rays.c */
t_ray				*camera_ray(t_camera *camera, t_vector *point);
t_ray				*scene_ray(t_vector *origin, t_vector *point);
void				free_ray(t_ray *ray);

/* ray_tracer.c */
t_vector			*ray_point(t_ray *ray, float t);
t_color				*trace_ray(t_scene *scene, t_ray *ray);

/* main.c */
void				setup_scene(t_scene *scene);

#endif
