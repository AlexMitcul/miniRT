//
// Created by amitcul on 6/24/23.
//

#ifndef MINIRT_LIGHT_H
#define MINIRT_LIGHT_H

#include "minirt.h"

typedef struct s_ambient_light
{
	t_color *color;
	float lighting_ratio;
} t_ambient_light;

typedef struct s_light
{
	t_vector *origin;
	float brightness_ratio;
	t_color *color;
} t_light;

#endif //MINIRT_LIGHT_H
