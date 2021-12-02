#include "minirt.h"
#include <limits.h>

#define T_MIN (double)0.00001
#define T_MAX (double)INT_MAX

// 球との衝突判定
// double	rt_hit_sphere(const t_vec3 *center, double radius, const t_ray *ray)
// {
// 	const t_vec3	oc = mr_vec3_sub(ray->origin, *center);
// 	const double	a = mr_vec3_length_squared(ray->direction);
// 	const double	half_b = mr_vec3_dot(oc, ray->direction);
// 	const double	c = mr_vec3_length_squared(oc) - radius * radius;
// 	const double	discriminant = half_b * half_b - a * c;

// 	if (discriminant < 0)
// 	{
// 		return (-1.0);
// 	}
// 	else
// 	{
// 		return (-half_b - sqrt(discriminant) / (2.0 * a));
// 	}
// }

static t_vec3	at(double t, const t_ray *ray)
{
	return (mr_vec3_add((ray->origin), (mr_vec3_mul_double(ray->direction, t))));
}

bool	rt_hit_sphere(const t_vec3 *center, double radius, const t_ray *ray, t_hit_record *rec)
{
	const t_vec3	oc = mr_vec3_sub(ray->origin, *center);
	const double	a = mr_vec3_length_squared(ray->direction);
	const double	half_b = mr_vec3_dot(oc, ray->direction);
	const double	c = mr_vec3_length_squared(oc) - radius * radius;
	const double	discriminant = half_b * half_b - a * c;

	if (discriminant > 0) // 衝突した場合
	{
		double root = sqrt(discriminant);
		double temp = (-half_b - root)/a;
		if (temp > T_MIN)
		{
			rec->t = temp;
			rec->p = at(rec->t, ray);
			rec->normal = mr_vec3_div_double(mr_vec3_sub(rec->p, *center), radius);
			return (true);
		}
		temp = (-half_b + root) / a;
		if (temp > T_MIN)
		{
			rec->t = temp;
			rec->p = at(rec->t, ray);
			rec->normal = mr_vec3_div_double(mr_vec3_sub(rec->p, *center), radius);
			return (true);
		}
	}
	return false;
}

