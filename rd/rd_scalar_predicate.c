#include "rd_read.h"

bool	rd_is_positive_real(const char *str)
{
	double	v;

	if (!str)
	{
		return (false);
	}
	v = rd_str_to_double(str);
	return (rd_is_finite(v) && 0 < v);
}

bool	rd_is_ratio(const char *str)
{
	double	v;

	if (!str)
	{
		return (false);
	}
	v = rd_str_to_double(str);
	return (rd_is_finite(v) && 0 <= v && v <= 1);
}

bool	rd_is_fov_angle(const char *str)
{
	double	v;

	if (!str)
	{
		return (false);
	}
	v = rd_str_to_double(str);
	return (rd_is_finite(v) && 0 <= v && v <= 180);
}
