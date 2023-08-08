/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:55:58 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/08 20:41:21 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
 * @ Description:
		* Validate file extension. Valid file extension is '.rt'.
		* file.rt.rt is valid extension.
 * @ Input:
		* const char *filename, which is path to file
 * @ Return value:
 	* If extension is valid => true, otherwise => false
 */
bool	is_valid_file_extension(const char *filename)
{
	char	*file_extension;

	if (!filename)
		return (false);
	file_extension = ft_strrchr(filename, '.');
	if (!file_extension)
		return (false);
	if (ft_strlen(file_extension) == ft_strlen(filename))
		return (false);
	if (ft_strlen(file_extension) == 3
		&& ft_strncmp(file_extension, ".rt", ft_strlen(file_extension)) == 0)
		return (true);
	return (false);
}

/*
 * @ Description:
	* Validate that line conforms for element type like:
	* A => 3 params, "A 0.2 255,255,255"
	* C => 4 params, "C -50.0,0.20 0,0,1 70
	* etc.
 * @ Input:
 	* char **data, array of strings divided by ' '. Array need to be NULL-ended!
 * @ Return value:
 	* If line is valid => true, otherwise => false
 */
bool	is_valid_line_items_count(char **data)
{
	char	*type;
	size_t	count;

	count = 0;
	while (data[count])
		count++;
	type = data[0];
	if (ft_strncmp(type, "A", ft_strlen(type)) == 0 && count == 3)
		return (true);
	else if (ft_strncmp(type, "C", ft_strlen(type)) == 0 && count == 4)
		return (true);
	else if (ft_strncmp(type, "L", ft_strlen(type)) == 0 && count == 4)
		return (true);
	else if (ft_strncmp(type, "sp", ft_strlen(type)) == 0 && count == 4)
		return (true);
	else if (ft_strncmp(type, "pl", ft_strlen(type)) == 0 && count == 4)
		return (true);
	else if (ft_strncmp(type, "cy", ft_strlen(type)) == 0 && count == 6)
		return (true);
	return (false);
}

int	parse_line(t_scene *scene, char *line)
{
	char	**splitted;
	char	*type;
	int		status;

	status = 0;
	splitted = ft_split(line, ' ');
	if (!splitted || !(*splitted))
		return (ft_free_strings(splitted), EXIT_FAILURE);
	if (is_valid_line_items_count(splitted) == false)
		return (ft_free_strings(splitted), EXIT_FAILURE);
	type = splitted[0];
	if (ft_strncmp(type, "A", ft_strlen(type)) == 0)
		status = parse_ambient_light(scene, splitted);
	if (ft_strncmp(type, "C", ft_strlen(type)) == 0)
		status = parse_camera(scene, splitted);
	else if (ft_strncmp(type, "L", ft_strlen(type)) == 0)
		status = parse_light(scene, splitted);
	else if (ft_strncmp(type, "sp", ft_strlen(type)) == 0)
		status = parse_sphere(scene, splitted);
	else if (ft_strncmp(type, "pl", ft_strlen(type)) == 0)
		status = parse_plane(scene, splitted);
	else if (ft_strncmp(type, "cy", ft_strlen(type)) == 0)
		status = parse_cylinder(scene, splitted);
	ft_free_strings(splitted);
	return (status);
}

int	parse_file(t_scene *scene, int fd)
{
	size_t	line_index;
	int		status;
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	line_index = 1;
	while (line)
	{
		if (ft_strncmp("\n", line, 2) != 0)
		{
			tmp = ft_strtrim(line, " \n");
			free(line);
			line = tmp;
			status = parse_line(scene, line);
			free(line);
			if (status == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	return (EXIT_SUCCESS);
}

t_scene	*parser(const char *filename)
{
	t_scene	*scene;
	int		status;
	int		fd;

	scene = new_scene();
	if (is_valid_file_extension(filename) == false)
		return (free_scene(scene), NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 3)
		return (free_scene(scene), NULL);
	status = parse_file(scene, fd);
	if (status == EXIT_FAILURE)
	{
		free_scene(scene);
		scene = NULL;
	}
	close(fd);
	return (scene);
}
