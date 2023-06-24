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

// ! Need to test this
bool is_valid_line_items_count(char **splitted)
{
	char *type;
	size_t count;

	count = 0;
	while (splitted[count])
		count++;
	type = splitted[0];
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

//static void test_parser(char *filename)
//{
//	(void)filename;
//	test_is_valid_file_extension();
//}

void	parse_line(t_scene *scene, char *line, size_t line_index)
{
	char **splitted;
	char *type;

	splitted = ft_split(line, ' ');
	if (!splitted || !(*splitted))
		return ;
	if (is_valid_line_items_count(splitted) == false)
		handle_error(PARSER_ERROR, &line_index);
	type = splitted[0];
	if (ft_strncmp(type, "A", ft_strlen(type)) == 0)
		parse_ambient_light(scene, splitted, line_index);
	if (ft_strncmp(type, "C", ft_strlen(type)) == 0)
		parse_camera(scene, splitted, line_index);
//	else if (ft_strncmp(type, "L", ft_strlen(type)) == 0 && count == 4)
//		return (true);
//	else if (ft_strncmp(type, "sp", ft_strlen(type)) == 0 && count == 4)
//		return (true);
//	else if (ft_strncmp(type, "pl", ft_strlen(type)) == 0 && count == 4)
//		return (true);
//	else if (ft_strncmp(type, "cy", ft_strlen(type)) == 0 && count == 6)
//		return (true);
}

void parse_file(t_scene *scene, int fd)
{
	size_t	line_index;
	char	*line;
	char 	*tmp;

	line = get_next_line(fd);
	line_index = 1;
	while (line)
	{
		tmp = ft_strtrim(line, " \n");
		free(line);
		line = tmp;
		parse_line(scene, line, line_index);
		free(line);
		get_next_line(fd);
		line_index++;
	}
}

t_scene *parser(char *filename)
{
	t_scene *scene;
	int fd;

	scene = new_scene(0, 0);
	if (is_valid_file_extension(filename) == false)
        handle_error(FILE_EXTENSION_ERROR, NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 3)
		handle_error(FILE_NAME_ERROR, NULL);
	parse_file(scene, fd);

	return (scene);
}
