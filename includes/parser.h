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

t_scene *parser(char *);
int parse_file(t_scene *, int);

/*
 * Validation funcs
*/
bool is_valid_file_extension(char *filename);
bool is_valid_line_items_count(char **splitted);

void parse_camera(t_scene *scene, char **data, size_t line_index);
int	parse_ambient_light(t_scene *scene, char **data);

#endif
