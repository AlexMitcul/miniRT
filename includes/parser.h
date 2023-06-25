/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:55:46 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 16:55:46 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_H
#define PARSER_H

t_scene *parser(const char *filename);

/*
 * File
*/
int parse_file(t_scene *scene, int fd);
bool is_valid_file_extension(const char *filename);
bool is_valid_line_items_count(char **splitted);

/*
 * Camera
 */
int parse_camera(t_scene *scene, char **data);

/*
 * Light
 */
int	parse_ambient_light(t_scene *scene, char **data);

#endif
