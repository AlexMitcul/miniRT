/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:49:19 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/26 16:01:41 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

t_color	*new_color(const int r, const int g, const int b);
t_color	*new_color_from_string(const char *data);
void	free_color(t_color *color);
bool	color_compare(t_color *a, t_color *b);

#endif //MINIRT_COLOR_H
