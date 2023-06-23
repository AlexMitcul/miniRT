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

# include "../includes/minirt.h"

bool is_valid_file_extension(char *filename)
{
    
}

t_scene *parse_file(char *filename)
{
    if (is_valid_file_extension(filename) == false)
        handle_error(FILE_EXTENSION_ERROR)
}
