/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:55:28 by omartela          #+#    #+#             */
/*   Updated: 2024/05/02 11:52:18 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		++start;
	if (start > end)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[end]) && end > start)
		--end;
	ptr = malloc(sizeof(char) * (end - start) + 2);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, &s1[start], (end - start) + 2);
	return (ptr);
}
