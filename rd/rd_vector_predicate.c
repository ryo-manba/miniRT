#include "rd_read.h"

bool	rd_is_vector(const char *str)
{
	t_vec3			vec;

	if (!str)
		return (false);
	rd_vectorize(str, &vec);
	return (rd_is_finite(vec.x));
}

bool	rd_is_unit_vector(const char *str)
{
	t_vec3			vec;
	double			r2;

	if (!str)
		return (false);
	rd_vectorize(str, &vec);
	if (!rd_is_finite(vec.x))
		return (false);
	r2 = vec.x * vec.x + vec.y	 * vec.y + vec.z * vec.z;
	r2 = r2 - 1;
	if (r2 < 0)
		r2 = -r2;
	return (RD_EPSILON * RD_EPSILON > r2);
}

bool	rd_is_color_vector(const char *str)
{
	t_vec3			vec;

	if (!str)
		return (false);
	rd_vectorize(str, &vec);
	if (!rd_is_finite(vec.x))
		return (false);
	if (vec.x < 0 || 255 < vec.x)
		return (false);
	if (vec.y < 0 || 255 < vec.y)
		return (false);
	if (vec.z < 0 || 255 < vec.z)
		return (false);
	return (true);
}
