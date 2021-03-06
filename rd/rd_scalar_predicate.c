/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_scalar_predicate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:36:22 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/14 19:58:45 by corvvs           ###   ########.fr       */
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
		return (rd_print_error_cur(cur,
				"infinite or not within range [0,180]"));
	}
	return (true);
}

bool	rd_word_is_role_angle(t_file_cursor *cur, const char *str)
{
	double	v;

	if (!str)
	{
		return (rd_print_error_cur(cur, "no word"));
	}
	v = rd_str_to_double(str);
	if (!(rd_is_finite(v) && 0 <= v && v <= 360))
	{
		return (rd_print_error_cur(cur,
				"infinite or not within range [0,360]"));
	}
	return (true);
}

bool	rd_word_is_xpm_file_path(t_file_cursor *cur, const char *str)
{
	size_t	n;

	if (!str)
	{
		return (rd_print_error_cur(cur, "no word"));
	}
	n = ft_strlen(str);
	if (n < 5 || ft_strcmp(str + n - 4, ".xpm"))
	{
		return (rd_print_error_cur(cur, "given path seems not to be xpm."));
	}
	return (true);
}
