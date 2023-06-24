

#include "../../includes/minirt.h"

t_ambient_light *new_ambient_light(void)
{
	t_ambient_light *light;

	light = (t_ambient_light *) malloc(sizeof(t_ambient_light));
	light->color->r = 0;
	light->color->g = 0;
	light->color->b = 0;
	light->lighting_ratio = 0.0;
	return (light);
}

void	free_ambient_light(t_ambient_light *light)
{
	if (!light)
		return ;
	free(light);
}