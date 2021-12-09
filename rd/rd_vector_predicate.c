/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_vector_predicate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:36:02 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/09 09:59:25 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

bool	rd_word_is_vector(t_file_cursor *cur, const char *str)
{
	t_vec3			vec;

	if (!str)
	{
		return (rd_print_error_cur(cur, "no word"));
	}
	rd_vectorize(str, &vec);
	if (!rd_is_finite(vec.x))
	{
		return (rd_print_error_cur(cur, "failed to parse as vector"));
	}
	return (true);
}

bool	rd_word_is_unit_vector(t_file_cursor *cur, const char *str)
{
	t_vec3			vec;
	double			r2;

	if (!str)
	{
		return (rd_print_error_cur(cur, "no word"));
	}
	rd_vectorize(str, &vec);
	if (!rd_is_finite(vec.x))
	{
		return (rd_print_error_cur(cur, "failed to parse as vector"));
	}
	if (vec.x < -1 || 1 < vec.x
		|| vec.y < -1 || 1 < vec.y
		|| vec.z < -1 || 1 < vec.z)
	{
		return (rd_print_error_cur(cur, "not within range [-1,+1]"));
	}
	r2 = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	if (RD_UNIT_PREDICATE_EPSILON <= fabs(r2 - 1))
	{
		return (rd_print_error_cur(cur, "not normalized"));
	}
	return (true);
}

bool	rd_word_is_color_vector(t_file_cursor *cur, const char *str)
{
	t_vec3			vec;

	if (!str)
	{
		return (rd_print_error_cur(cur, "no word"));
	}
	rd_vectorize(str, &vec);
	if (!rd_is_finite(vec.x))
	{
		return (rd_print_error_cur(cur, "failed to parse as vector"));
	}
	if (vec.x < 0 || 255 < vec.x)
	{
		return (rd_print_error_cur(cur, "R is not within range [0,255]"));
	}
	if (vec.y < 0 || 255 < vec.y)
	{
		return (rd_print_error_cur(cur, "G is not within range [0,255]"));
	}
	if (vec.z < 0 || 255 < vec.z)
	{
		return (rd_print_error_cur(cur, "B is not within range [0,255]"));
	}
	return (true);
}
