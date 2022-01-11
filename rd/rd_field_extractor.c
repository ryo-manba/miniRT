/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_field_extractor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:04:41 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/11 21:05:41 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

bool	rd_extract_double_scalar(const char *str, void *slot)
{
	double	v;

	if (!str)
	{
		return (false);
	}
	v = rd_str_to_double(str);
	*(double *)slot = v;
	return (rd_is_finite(v));
}

bool	rd_extract_double_vector(const char *str, void *slot)
{
	t_vec3	*vecslot;

	if (!str)
	{
		return (false);
	}
	vecslot = (t_vec3 *)slot;
	rd_vectorize(str, vecslot);
	return (rd_is_finite(vecslot->x));
}

bool	rd_extract_string(const char *str, void *slot)
{
	char	*dupped;

	if (!str)
	{
		return (false);
	}
	dupped = ft_strdup(str);
	if (!dupped)
	{
		return (false);
	}
	*(char **)slot = dupped;
	return (ft_strlen(str) > 0);
}
