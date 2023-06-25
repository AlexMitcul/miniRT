#ifndef MINIRT_COLOR_H
#define MINIRT_COLOR_H

typedef struct s_color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} t_color;

t_color *new_color(const int r, const int g, const int b);
t_color *new_color_from_string(const char *data);

void	free_color(t_color *color);

#endif //MINIRT_COLOR_H
