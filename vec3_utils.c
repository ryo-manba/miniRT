#include <math.h>
#include "vec3.h"

double	vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

t_vec3	vec3_mul_double(t_vec3 u, double t)
{
	t_vec3	vec;

	vec.x = u.x * t;
	vec.y = u.y * t;
	vec.z = u.z * t;
	return (vec);
}

// ベクトルとdoubleの除算
t_vec3	vec3_div(t_vec3 v, double t)
{
	return (vec3_mul_double(v, (1 / t)));
}

// 単位ベクトル
t_vec3 unit_vector(t_vec3 v)
{
	const double length = vec3_length(v);

	return (vec3_div(vec3_mul_double(v), length));
}