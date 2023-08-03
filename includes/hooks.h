/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:45:40 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/02 19:51:50 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

void	display_menu(t_scene *scene);
void	render_menu(t_scene *scene);
void	display_info(t_scene *scene);

int		close_win(int keycode, t_scene *scene);
int		close_win_with_cross(void *data);

void	display_spheres_info(t_scene *scene);
void	display_plane_info(t_scene *scene);
void	display_cylinder_info(t_scene *scene);
void	display_light_info(t_scene *scene);

/* utils */

char	*get_coordinates(t_vector *vector, int precision);
char	*get_color_in_hex_string(t_color *color);

#endif
