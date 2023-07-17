/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:52:08 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 10:52:24 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "minirt.h"

typedef struct s_ambient_light
{
	t_color	*color;
	float	lighting;
}	t_ambient_light;

t_ambient_light	*new_ambient_light(t_color *color, float lighting);
void			free_ambient_light(t_ambient_light *ambient_light);

typedef struct s_light
{
	t_vector	*origin;
	float		brightness;
	t_color		*color;
}	t_light;

t_light			*new_light(t_vector *origin, float brightness, t_color *color);
void			free_light(t_light *light);

#endif //MINIRT_LIGHT_H
