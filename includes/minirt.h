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
# include "color.h"
# include "light.h"
# include "error.h"
# include "sphere.h"
# include "camera.h"
# include "scene.h"
# include "parser.h"

# include "tests.h"

int ft_atof(float *to_return, const char *s);
void ft_free_strings(char** array);
int	ft_isdecimal(const char *str);

#endif