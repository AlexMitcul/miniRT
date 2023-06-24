//
// Created by amitcul on 6/24/23.
//

#ifndef MINIRT_COLOR_H
#define MINIRT_COLOR_H

typedef struct s_color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} t_color;

void	free_color(t_color *color);
t_color *new_color_from_string(const char *data);

#endif //MINIRT_COLOR_H
