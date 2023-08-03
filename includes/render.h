/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:30:16 by amenses-          #+#    #+#             */
/*   Updated: 2023/07/28 02:05:48 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

# define PI 	3.14159265358979323846264338
# define MAX_T	10000000000


typedef struct s_intersection
{
	t_vector				*p;
	t_vector				*n;
	float					t;
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

t_ray		*new_ray(t_vector *origin, t_vector *point);
t_vector	*ray_point(t_ray *ray, float t);
void		free_ray(t_ray *ray);

#endif
