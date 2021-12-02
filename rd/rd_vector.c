/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:36:04 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/01 14:25:13 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

static size_t	strarraylen(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		i += 1;
	}
	return (i);
}

void	rd_free_strarray(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	rd_vectorize(const char *str, t_vec3 *vector)
{
	char			**splitted;

	vector->x = rd_nan();
	vector->y = rd_nan();
	vector->z = rd_nan();
	splitted = ft_split(str, ',');
	if (!splitted)
		return ;
	if (strarraylen(splitted) == 3)
	{
		vector->x = rd_str_to_double(splitted[0]);
		vector->y = rd_str_to_double(splitted[1]);
		vector->z = rd_str_to_double(splitted[2]);
		if (rd_is_finite(vector->x) && rd_is_finite(vector->y)
			&& rd_is_finite(vector->z))
		{
			rd_free_strarray(splitted);
			return ;
		}
	}
	vector->x = rd_nan();
	vector->y = rd_nan();
	vector->z = rd_nan();
	rd_free_strarray(splitted);
}
