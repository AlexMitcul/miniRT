/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:13:29 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/02 19:51:39 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

char	*ft_ftoa(float n, int precision)
{
	char	*str;
	char	*tmp;
	char	*result;
	int		i;

	str = ft_itoa((int)n);
	if (precision == 0)
		return (str);
	tmp = ft_strjoin(str, ".");
	free(str);
	i = 0;
	while (i < precision)
	{
		n = n * 10;
		str = ft_itoa((int)n);
		result = ft_strjoin(tmp, str);
		free(tmp);
		free(str);
		tmp = result;
		n = n - (int)n;
		i++;
	}
	return (tmp);
}

char	*get_coordinates(t_vector *vector, int precision)
{
	char	*to_print;
	char	*tmp;
	char	*tmp2;

	to_print = ft_ftoa(vector->x, precision);
	tmp = ft_strjoin(to_print, "  ");
	free(to_print);
	to_print = ft_ftoa(vector->y, precision);
	tmp2 = ft_strjoin(tmp, to_print);
	free(tmp);
	free(to_print);
	tmp = ft_strjoin(tmp2, "  ");
	free(tmp2);
	to_print = ft_ftoa(vector->z, precision);
	tmp2 = ft_strjoin(tmp, to_print);
	free(tmp);
	free(to_print);
	return (tmp2);
}

void	display_camera_info(t_scene *scene)
{
	char	*to_print;

	mlx_string_put(scene->mlx, scene->win, 10, 20, 0xffffff,
		"Camera:");
	mlx_string_put(scene->mlx, scene->win, 10, 40, 0xffffff,
		"x       y       z");
	to_print = get_coordinates(scene->camera->origin, 2);
	mlx_string_put(scene->mlx, scene->win, 10, 60, 0xffffff,
		to_print);
	free(to_print);
	to_print = get_coordinates(scene->camera->direction, 3);
	mlx_string_put(scene->mlx, scene->win, 10, 80, 0xffffff,
		to_print);
	free(to_print);
}

char	*ft_itoa_base(int n, int base)
{
	char	*str;
	char	*hex;
	int		i;
	int		len;

	if (n == 0 && base == 16)
		return (ft_strdup("00"));
	hex = "0123456789abcdef";
	len = 1;
	i = n;
	while (i /= base)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len--)
	{
		str[len] = hex[n % base];
		n /= base;
	}
	return (str);
}

static char	*split_strings(char *a, char *b, char *c, char *delimeter)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(a, delimeter);
	tmp2 = ft_strjoin(tmp, b);
	free(tmp);
	tmp = ft_strjoin(tmp2, delimeter);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, c);
	free(tmp);
	return (tmp2);
}

char	*get_color_in_hex_string(t_color *color)
{
	char	*r;
	char	*g;
	char	*b;
	char	*result;

	r = ft_itoa_base(color->r, 16);
	g = ft_itoa_base(color->g, 16);
	b = ft_itoa_base(color->b, 16);
	result = split_strings(r, g, b, "");
	free(r);
	free(g);
	free(b);
	r = ft_strjoin("0x", result);
	free(result);
	return (r);
}

void	display_figures_info(t_scene *scene)
{
	display_camera_info(scene);
	display_light_info(scene);
	display_spheres_info(scene);
	display_plane_info(scene);
	display_cylinder_info(scene);
}

#define MENU_OFFSET 700

void	display_info(t_scene *scene)
{
	display_figures_info(scene);
	mlx_string_put(scene->mlx, scene->win, 10, MENU_OFFSET + 20, 0xffff00,
				   " exit        ESQ/window cross");
  	mlx_string_put(scene->mlx, scene->win, 10, MENU_OFFSET + 40, 0xffff00,
					 " press 0:           menu");
	mlx_string_put(scene->mlx, scene->win, 10, MENU_OFFSET + 80, 0xffff00,
				   " change object        left/right arrow");
	mlx_string_put(scene->mlx, scene->win, 10, MENU_OFFSET + 100, 0xffff00,
				   " change object type   up/down arrow");
  	mlx_string_put(scene->mlx, scene->win, 10, MENU_OFFSET + 140, 0xffff00,
					 " == numpad section == ");
	mlx_string_put(scene->mlx, scene->win, 10, MENU_OFFSET + 160, 0xffff00,
				   " change Z coord +/-      2 | 8");
	mlx_string_put(scene->mlx, scene->win, 10, MENU_OFFSET + 160, 0xffff00,
				 " change X coord +/-      6 | 4");
	mlx_string_put(scene->mlx, scene->win, 10, MENU_OFFSET + 160, 0xffff00,
				   " change Y coord +/-      + | -");
	mlx_string_put(scene->mlx, scene->win, 10, MENU_OFFSET + 220, 0xffff00,
		" press P:             perspective mode");
	mlx_string_put(scene->mlx, scene->win, 10, MENU_OFFSET + 240, 0xffff00,
		" press S:             depth-shade mode");
}
