/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raw_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 23:39:38 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/13 14:30:48 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_all_free(char **split_strs, size_t i)
{
	while (i--)
	{
		free(split_strs[i]);
		split_strs[i] = NULL;
	}
	free(split_strs);
	return (NULL);
}

static char	*ft_memdup(char const *s, size_t n)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s, n);
	dest[n] = '\0';
	return (dest);
}

static void	*get_split(char **split_strs, char const *s, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	while (*s)
	{
		n = 0;
		if (0 < i && s[n] && s[n] == c)
			s += 1;
		while (s[n] && s[n] != c)
			n += 1;
		split_strs[i] = ft_memdup(s, n);
		if (split_strs[i] == NULL)
			return (ft_all_free(split_strs, i));
		i++;
		s += n;
	}
	split_strs[i] = NULL;
	return (split_strs);
}

static size_t	get_len(char const *s, char c)
{
	size_t	cnt;

	cnt = 1;
	while (*s)
	{
		if (*s == c)
			cnt++;
		s++;
	}
	return (cnt);
}

char	**ft_rawsplit(char const *s, char c)
{
	char	**split_strs;
	size_t	split_len;

	if (s == NULL)
		return (NULL);
	split_len = get_len(s, c);
	split_strs = (char **)malloc(sizeof(char *) * (split_len + 1));
	if (split_strs == NULL)
		return (NULL);
	return (get_split(split_strs, s, c));
}
