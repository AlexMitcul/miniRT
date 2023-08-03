

#include "../../includes/vector.h"

void	update(t_vector *vector, t_coordinate coordinate, float by)
{
  if (coordinate == X)
	vector->x += by;
  else if (coordinate == Y)
	vector->y += by;
  else if (coordinate == Z)
	vector->z += by;
}
