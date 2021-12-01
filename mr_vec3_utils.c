#include <math.h>
#include "mr_vec3.h"

double	mr_vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	mr_vec3_length(t_vec3 v)
{
	return (sqrt(mr_vec3_length_squared(v)));
}

t_vec3	mr_vec3_mul_double(t_vec3 u, double t)
{
	t_vec3	vec;

	vec.x = u.x * t;
	vec.y = u.y * t;
	vec.z = u.z * t;
	return (vec);
}

t_vec3	mr_vec3_div_double(t_vec3 v, double t)
{
	return (mr_vec3_mul_double(v, (1 / t)));
}

// 単位ベクトル
t_vec3	mr_unit_vector(t_vec3 v)
{
	return (mr_vec3_div_double(v, mr_vec3_length(v)));
}
