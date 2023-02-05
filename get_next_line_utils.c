/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyang   < jinyang@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 01:30:49 by jinyang           #+#    #+#             */
/*   Updated: 2022/07/25 07:18:30 by jinyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s++) != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	i;

	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	unsigned int	i;

	i = 0;
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	ch = c;
	while (*s != '\0')
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (!c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len1;
	unsigned int	len2;
	char			*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (result == NULL)
		return (result);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcpy(result + len1, s2, len2 + 1);
	return (result);
}
