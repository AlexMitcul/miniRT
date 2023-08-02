/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:42:19 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/02 19:29:04 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void render(t_scene *scene)
{
	render_sphere(scene);
	free_menu(scene);
	if (scene->is_menu_open)
		render_menu(scene);
}
