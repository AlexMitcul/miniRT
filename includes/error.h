/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:41:54 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 10:51:30 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error
{
	MEMORY_ERROR = 3,
	ARGUMENTS_COUNT_ERROR,
	FILE_NAME_ERROR,
	FILE_EXTENSION_ERROR,
	PARSER_ERROR,
	PARSER_FLOAT_ERROR,
	BAD_VALUE_ERROR,
}	t_error;

void	handle_error(t_error error, void *data);

#endif
