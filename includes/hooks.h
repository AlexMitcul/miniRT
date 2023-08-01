/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:45:40 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/01 17:15:16 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

void	display_menu(t_scene *scene);
void	render_menu(t_scene *scene);
void	display_info(t_scene *scene);

int		close_win(int keycode, t_scene *scene);
int		close_win_with_cross(void *data);

#endif
