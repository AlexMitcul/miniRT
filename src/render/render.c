/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:42:19 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/03 15:22:10 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <time.h>
void render(t_scene *scene)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();

  	scene->is_busy = true;
	render_sphere(scene);
	free_menu(scene);
	if (scene->is_menu_open)
		render_menu(scene);
	scene->is_busy = false;

  	end = clock();

	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  	printf("Execution time: %f seconds\n", cpu_time_used);
}
