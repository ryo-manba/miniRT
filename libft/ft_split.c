/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 22:32:23 by rmatsuka          #+#    #+#             */
/*   Updated: 2022/01/13 14:45:14 by corvvs           ###   ########.fr       */
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

static char	*ft_strcpy(char const *s, char c)
{
	char	*dest;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static size_t	get_len(char const *s, char c)
{
	size_t			i;
	size_t			cnt;

	i = 0;
	cnt = 0;
	if (s[i] && s[i] != c)
		cnt++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			cnt++;
		i++;
	}
	return (cnt);
}

static void	*get_split(char **split_strs, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			split_strs[i] = ft_strcpy(s, c);
			if (split_strs[i] == NULL)
				return (ft_all_free(split_strs, i));
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	split_strs[i] = NULL;
	return (split_strs);
}

char	**ft_split(char const *s, char c)
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
