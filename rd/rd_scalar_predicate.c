/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_scalar_predicate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:36:22 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/08 20:56:32 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

bool	rd_word_is_positive_real(const char *str)
{
	double	v;

	if (!str)
	{
		return (false);
	}
	v = rd_str_to_double(str);
	return (rd_is_finite(v) && 0 < v);
}

bool	rd_word_is_ratio(const char *str)
{
	double	v;

	if (!str)
	{
		return (false);
	}
	v = rd_str_to_double(str);
	return (rd_is_finite(v) && 0 <= v && v <= 1);
}

bool	rd_word_is_fov_angle(const char *str)
{
	double	v;

	if (!str)
	{
		return (false);
	}
	v = rd_str_to_double(str);
	return (rd_is_finite(v) && 0 <= v && v <= 180);
}
