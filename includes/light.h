//
// Created by amitcul on 6/24/23.
//

#ifndef MINIRT_LIGHT_H
#define MINIRT_LIGHT_H

#include "minirt.h"

typedef struct s_ambient_light
{
	t_color *color;
	float lighting;
} t_ambient_light;

t_ambient_light *new_ambient_light(t_color *color, float lighting);
void    free_ambient_light(t_ambient_light *ambient_light);

typedef struct s_light
{
	t_vector *origin;
	float brightness;
	t_color *color;
} t_light;

t_light *new_light(t_vector *origin, float brightness, t_color *color);
void    free_light(t_light *light);

#endif //MINIRT_LIGHT_H
