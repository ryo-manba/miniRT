/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_scalar_predicate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:36:22 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/09 09:56:52 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

bool	rd_word_is_positive_real(t_file_cursor *cur, const char *str)
{
	double	v;

	if (!str)
	{
		return (rd_print_error_cur(cur, "no word"));
	}
	v = rd_str_to_double(str);
	if (!(rd_is_finite(v) && 0 < v))
	{
		return (rd_print_error_cur(cur, "infinite or not positive"));
	}
	return (true);
}

bool	rd_word_is_ratio(t_file_cursor *cur, const char *str)
{
	double	v;

	if (!str)
	{
		return (rd_print_error_cur(cur, "no word"));
	}
	v = rd_str_to_double(str);
	if (!(rd_is_finite(v) && 0 <= v && v <= 1))
	{
		return (rd_print_error_cur(cur, "infinite or not within range [0,1]"));
	}
	return (true);
}

bool	rd_word_is_fov_angle(t_file_cursor *cur, const char *str)
{
	double	v;

	if (!str)
	{
		return (rd_print_error_cur(cur, "no word"));
	}
	v = rd_str_to_double(str);
	if (!(rd_is_finite(v) && 0 <= v && v <= 180))
	{
		return (rd_print_error_cur(cur, "infinite or not within range [0,180]"));
	}
	return (true);
}
