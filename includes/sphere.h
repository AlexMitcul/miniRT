/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:08:26 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/26 00:39:43 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "minirt.h"
# include "scene.h"

typedef struct s_sphere
{
	t_vector		*center;
	float			radius;
	t_color			*color;
	struct s_sphere	*next;
}	t_sphere;

t_sphere	*new_sphere(t_vector *center, float radius, t_color *color);
void		free_sphere(t_sphere *sphere);
void		free_sphere_list(t_sphere *head);
void		sphere_add_to_scene(t_scene *scene, t_sphere *sphere);

#endif
