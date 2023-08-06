/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:54:25 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/06 18:20:36 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "minirt.h"

typedef struct s_plane
{
	t_vector		*origin;
	t_vector		*direction;
	t_color			*color;
	int				is_cylinder_cap;
	struct s_plane	*next;
}	t_plane;

t_plane	*new_plane(t_vector *origin, t_vector *direction, t_color *color);
void	free_plane(t_plane *plane);
void	free_plane_list(t_plane *head);
void	plane_add_to_scene(t_scene *scene, t_plane *plane);

#endif //MINIRT_PLANE_H
