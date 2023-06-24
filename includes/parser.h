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

t_scene *parse_file(char *);

/*
 * Validation funcs
*/
bool is_valid_file_extension(char *filename);

#endif
