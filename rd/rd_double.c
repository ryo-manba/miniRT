/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:36:15 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/01 11:36:16 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rd_read.h"

double	rd_inf(bool positive)
{
	t_ull_double	u;

	u.ull = (1ull << 63) - (1ull << 52);
	if (!positive)
	{
		u.ull |= (1ull << 63);
	}
	return (u.dbl);
}

// returns a nan
double	rd_nan(void)
{
	t_ull_double	u;

	u.ull = (1ull << 63) - (1ull << 52) + 1;
	return (u.dbl);
}

// is a val not infinite or nan?
bool	rd_is_finite(const double val)
{
	t_ull_double		u;
	unsigned long long	fullbit;

	fullbit = (1ull << 11) - 1ull;
	u.dbl = val;
	return (((u.ull >> 52) & fullbit) != fullbit);
}

double	rd_str_to_double(const char* str)
{
	double	val;
	double	sign;
	double	exp;
	bool	dot;

	val = 0;
	dot = false;
	exp = 1;
	sign = 1 - (*str == '-') * 2;
	if (*str == '+' || *str == '-')
		str += 1;
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			if (dot)
				val = val + exp * (*str - '0');
			else
				val = val * 10 + *str - '0';
		}
		else if (*str == '.' && !dot)
			dot = true;
		else
			return (rd_nan());
		str += 1;
		if (dot)
			exp = exp / 10;
	}
	if (rd_is_finite(val))
		return (val * sign);
	else
		return (rd_nan());
}
