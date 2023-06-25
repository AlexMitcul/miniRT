/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:51:47 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 15:51:47 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int main(int argc, char **argv)
{
    t_scene *scene;

	test();
    if (argc != 2)
        handle_error(ARGUMENTS_COUNT_ERROR, NULL);
    scene = parser(argv[1]);
	free_scene(scene);

    return (0);
}