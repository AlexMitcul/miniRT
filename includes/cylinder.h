/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:49:52 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/07 20:10:25 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "minirt.h"

typedef struct s_cylinder
{
	t_vector			*center;
	t_vector			*axis;
	float				radius;
	float				height;
	t_color				*color;
	t_plane				*cap[2];
	struct s_cylinder	*next;
	struct s_cylinder	*prev;
}						t_cylinder;

t_cylinder	*new_cylinder(t_vector *center, t_vector *axis,
				float num_data[2], t_color *color);
void		free_cylinder(t_cylinder *cylinder);
void		free_cylinder_list(t_cylinder *head);
void		cylinder_add_to_scene(t_scene *scene,
				t_cylinder *cylinder);

#endif //MINIRT_CYLINDER_H
