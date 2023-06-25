
#include "../../includes/minirt.h"

bool is_valid_vector_string(const char *str)
{
	size_t	length;
	size_t	i;

	if (!str || ft_count_chat(str, '.') != 3 || ft_count_chat(str, ',') != 3)
		return (false);
	length = ft_strlen(str);
	if (ft_strchr(".,", str[0]) || ft_strchr(".,", str[length]))
		return (false);
	i = 0;
	while (i < length - 1)
	{
		if (ft_strchr(".,", str[i]) && !ft_isdigit(str[i + 1]))
			return (false);
		i++;
	}
	return (true);
}