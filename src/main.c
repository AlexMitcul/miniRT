/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:51:47 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 10:45:44 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_scene	*scene;
	void	*mlx;
	void	*win;
	void	*img;

	//	test();
	if (argc != 2)
		handle_error(ARGUMENTS_COUNT_ERROR, NULL);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920/2, 1080/2, "miniRT");
	img = mlx_new_image(mlx, 1920/2, 1080/2);
	if (!mlx)
		return (2);
	scene = parser(argv[1]);
	free_scene(scene);
	mlx_loop(mlx);
	return (0);
}
