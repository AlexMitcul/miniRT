#include "../../includes/minirt.h"

t_vector    *vec_substract(t_vector *a, t_vector *b)
{
	t_vector    *result;

	result = new_vector(a->x - b->x, a->y - b->y, a->z - b->z);
	return (result);
}

float   vec_length(t_vector *v)
{
	float   result;

	result = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	return (result);
}

void    vec_normalize(t_vector *v)
{
	float   length;

	length = vec_length(v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

float   vec_product(t_vector *a, t_vector *b)
{
	float   result;

	result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	return (result);
}