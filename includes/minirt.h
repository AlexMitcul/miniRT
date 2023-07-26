/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:40:07 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/26 01:32:52 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stddef.h>
# include <math.h>
# include <stdbool.h>

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"

# include "../minilibx-linux/mlx.h"

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
# include "render.h"

# include "test.h"

float	ft_atof(const char *str);
void	ft_free_strings(char **array);
int		ft_isdecimal(const char *str);
int		ft_is_decimal_in_range(const char *str, int low, int high);
bool	is_color_string(const char *line);
bool	is_float(const char *str);
size_t	ft_count_char(const char *str, char c);
bool	is_unsigned_char_datatype(char **data);

int		close_win(int keycode, t_scene *scene);
int		close_win_with_cross(void *data);

#endif
