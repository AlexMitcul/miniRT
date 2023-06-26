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
# include "scene.h"
# include "color.h"
# include "plane.h"
# include "light.h"
# include "error.h"
# include "sphere.h"
# include "cylinder.h"
# include "camera.h"
# include "parser.h"


# include "test.h"

float ft_atof(const char* str);
void ft_free_strings(char** array);
int	ft_isdecimal(const char *str);
int ft_is_decimal_in_range(const char *str, int low, int high);
bool is_color_string(const char *line);
bool is_float(const char* str);
size_t	ft_count_chat(const char *str, char c);

#endif