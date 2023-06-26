#include <stdlib.h>

void ft_free_strings(char** array)
{
	if (array == NULL || *array == NULL)
		return;
	int i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
