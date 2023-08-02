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

void	display_light_info(t_scene *scene)
{
	char	*to_print;

	mlx_string_put(scene->mlx, scene->win, 10, 100 + 20, 0xffffff,
		"Light:");
	mlx_string_put(scene->mlx, scene->win, 10, 100 + 40, 0xffffff,
		"x       y       z");
	to_print = get_coordinates(scene->light->origin, 2);
	mlx_string_put(scene->mlx, scene->win, 10, 100 + 60, 0xffffff,
		to_print);
	free(to_print);
	to_print = get_color_in_hex_string(scene->light->color);
	mlx_string_put(scene->mlx, scene->win, 10, 100 + 80, rgb2int(scene->light->color),
		to_print);
	free(to_print);
}

void	display_figures_info(t_scene *scene)
{
	display_camera_info(scene);
	display_light_info(scene);
	display_spheres_info(scene);
	display_plane_info(scene);
	display_cylinder_info(scene);
}

void	display_info(t_scene *scene)
{
	display_figures_info(scene);
	mlx_string_put(scene->mlx, scene->win, 10, 700 + 20, 0xffff00,
		" press ESC:           exit");
	mlx_string_put(scene->mlx, scene->win, 10, 700 + 80, 0xffff00,
		" left mouse button:   rotation");
	mlx_string_put(scene->mlx, scene->win, 10, 700 + 100, 0xffff00,
		" right mouse button:  translation");
	mlx_string_put(scene->mlx, scene->win, 10, 700 + 120, 0xffff00,
		" scroll up/down:      zoom in/out");
	mlx_string_put(scene->mlx, scene->win, 10, 700 + 140, 0xffff00,
		" press C:             change color mode");
	mlx_string_put(scene->mlx, scene->win, 10, 700 + 160, 0xffff00,
		" press H:             help");
	mlx_string_put(scene->mlx, scene->win, 10, 700 + 180, 0xffff00,
		" press I:             isometric mode");
	mlx_string_put(scene->mlx, scene->win, 10, 700 + 200, 0xffff00,
		" press P:             perspective mode");
	mlx_string_put(scene->mlx, scene->win, 10, 700 + 220, 0xffff00,
		" press S:             depth-shade mode");
}

/*
Camera:
x	y	z
0.0	0.0	0.0
0.00 0.01 1.02

Light:
0x00FF00
x	y	z
0.0	0.0	0.0

Plane
0x00FF00
x	y	z
0.0	0.0	0.0
0.00 0.01 1.02

Sphere
0x00FF00
x	y	z
0.0	0.0	0.0

Cylinder
0x00FF00
x	y	z
0.0	0.0	0.0
0.00 0.01 1.02
*/
