#include "mr_vec3.h"

t_vec3  vec3_add(t_vec3 u, t_vec3 v)
{
	t_vec3	add;

	add.x = u.x + v.x;
	add.y = u.y + v.y;
	add.z = u.z + v.z;
	return (add);
}

t_vec3  vec3_sub(t_vec3 u, t_vec3 v)
{
	t_vec3	sub;

	sub.x = u.x - v.x;
	sub.y = u.y - v.y;
	sub.z = u.z - v.z;
	return (sub);
}

t_vec3  vec3_mul(t_vec3 u, t_vec3 v)
{
	t_vec3	mul;

	mul.x = u.x * v.x;
	mul.y = u.y * v.y;
	mul.z = u.z * v.z;
	return (mul);
}

double  vec3_dot(t_vec3 u, t_vec3 v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

t_vec3	vec3_cross(t_vec3 u, t_vec3 v)
{
	t_vec3	cross;

	cross.x = u.y * v.z - u.z * v.y;
	cross.y = u.z * v.x - u.x * v.z;
	cross.z = u.x * v.y - u.y * v.x;
	return (cross);
}
