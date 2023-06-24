/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:42:19 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 15:42:19 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    handle_error(t_error error)
{
    if (error == MEMORY_ERROR)
        ft_putstr_fd("Error: Memory allocation failed.\n", STDERR_FILENO);
    exit(EXIT_FAILURE);

}