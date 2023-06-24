/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:40:07 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 15:40:07 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINIRT_H
#define MINIRT_H

# include <stdlib.h>
# include <stddef.h>
# include <math.h>
# include <stdbool.h>

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"

# include "vector.h"
# include "error.h"
# include "sphere.h"
# include "camera.h"
# include "scene.h"
# include "parser.h"

# include "tests.h"

int ft_atof(float *to_return, const char *s);

#endif