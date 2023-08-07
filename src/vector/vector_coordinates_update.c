/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_coordinates_update.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:21:10 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/07 20:21:18 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

void	update(t_vector *vector, t_coordinate coordinate, float by)
{
	if (coordinate == X)
		vector->x += by;
	else if (coordinate == Y)
		vector->y += by;
	else if (coordinate == Z)
		vector->z += by;
}
