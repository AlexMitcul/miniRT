

#include "../../includes/minirt.h"

t_ambient_light *new_ambient_light(t_color *color, float lighting)
{
	t_ambient_light *light;

    if (!color)
        return (NULL);
	light = (t_ambient_light *) malloc(sizeof(t_ambient_light));
    if (!light)
        return (NULL);
    light->color = color;
	light->lighting = lighting;
	return (light);
}

void	free_ambient_light(t_ambient_light *light)
{
	if (!light)
		return ;
	free(light);
}

t_light *new_light(t_vector *origin, float brightness, t_color *color)
{
    t_light *light;

    if (!color)
        return (NULL);
    light = (t_light *) malloc(sizeof(t_light));
    if (!light)
        return (NULL);
    light->origin = origin;
    light->brightness = brightness;
    light->color = color;
    return (light);
}