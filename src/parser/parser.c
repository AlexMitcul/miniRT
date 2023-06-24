/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:55:58 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 16:55:58 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minirt.h"

bool is_valid_file_extension(char *filename)
{
	char *file_extension;

    if (!filename)
		return (false);
	file_extension = ft_strrchr(filename, '.');
	if (!file_extension)
		return (false);
	if (ft_strlen(file_extension) == ft_strlen(filename))
		return (false);
	if (ft_strlen(file_extension) == 3 &&
		ft_strncmp(file_extension, ".rt", ft_strlen(file_extension)) == 0)
		return (true);
	return (false);
}


t_scene *parse_file(char *filename)
{
	t_scene *scene;

	scene = new_scene(0, 0);
	(void)filename;
	test_is_valid_file_extension();

//    if (is_valid_file_extension(filename) == false)
//        handle_error(FILE_EXTENSION_ERROR)
	return (scene);
}
