/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:30:16 by amenses-          #+#    #+#             */
/*   Updated: 2023/07/26 16:52:14 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

# define PI 		3.14159265358979323846264338
# define MAX_T      1000000000

void	render(t_scene *scene);
void	render_sphere(t_scene *scene);
int     new_image(t_scene *scene);

#endif
