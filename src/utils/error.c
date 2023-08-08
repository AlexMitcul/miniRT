/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:42:19 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/08 18:09:44 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// static void	parser_error_handler(size_t line_index)
// {
// 	char	*line;

// 	ft_putstr_fd("Error\n\tParser error at line ", STDERR_FILENO);
// 	line = ft_itoa(line_index);
// 	ft_putstr_fd(line, STDERR_FILENO);
// 	ft_putstr_fd(".\n", STDERR_FILENO);
// 	free(line);
// }

// void	handle_error(t_error error, void *data)
// {
// 	if (error == MEMORY_ERROR)
// 		ft_putstr_fd("Error\n\tMemory allocation failed.\n", STDERR_FILENO);
// 	else if (error == ARGUMENTS_COUNT_ERROR)
// 		ft_putstr_fd("Error\n\tArguments count error.\n", STDERR_FILENO);
// 	else if (error == FILE_NAME_ERROR)
// 		ft_putstr_fd("Error\n\tCannot open file.\n", STDERR_FILENO);
// 	else if (error == FILE_EXTENSION_ERROR)
// 		ft_putstr_fd("Error\n\tFile extension error.\n", STDERR_FILENO);
// 	else if (error == PARSER_ERROR)
// 		parser_error_handler(*((size_t *)data));
// 	exit(EXIT_FAILURE);
// }
