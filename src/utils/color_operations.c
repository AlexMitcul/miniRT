/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:40:46 by amenses-          #+#    #+#             */
/*   Updated: 2023/07/26 22:53:08 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	*color_multiply(float scalar, t_color *color)
{
	t_color	*result;

	result = new_color(color->r * scalar, color->g * scalar, color->b * scalar);
	return (result);
}

t_color	*color_dup(t_color *color)
{
	t_color	*result;

	result = new_color(color->r, color->g, color->b);
	return (result);
}
