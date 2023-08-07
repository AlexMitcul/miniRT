/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:54:25 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/07 18:24:54 by amitcul          ###   ########.fr       */
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
	struct s_plane	*prev;
}	t_plane;

t_plane	*new_plane(t_vector *origin, t_vector *direction, t_color *color);
void	free_plane(t_plane *plane);
void	free_plane_list(t_plane *head);
void	plane_add_to_scene(t_scene *scene, t_plane *plane);

#endif //MINIRT_PLANE_H
