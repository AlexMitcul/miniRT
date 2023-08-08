/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:56:50 by amenses-          #+#    #+#             */
/*   Updated: 2022/11/14 01:22:21 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_isset(s1[start], set) && start < end + 1)
		start++;
	if (start < end + 1)
	{
		while (ft_isset(s1[end], set) && end > 0)
			end--;
	}
	return (ft_substr(s1, start, end - start + 1));
}
/* int main(void)
{
	char *s = "  \t \t \n   \n\n\n\t";
	char *set = " \n\t";
	char *trim;

	trim = ft_strtrim(s, set);
	printf(".%s.\n", trim);
	free(trim);
	return (0);
} */