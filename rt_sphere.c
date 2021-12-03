#include "minirt.h"
#include <limits.h>

#define EPS 1e-8

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

	if (discriminant > 0) // 交差判定
	{
		double root = sqrt(discriminant);
		double t = 0;
		if (((-half_b - root) / a) > EPS)
		{
			t = (-half_b - root) / a;
		}
		else if (((-half_b + root) / a) > EPS)
		{
			t = (-half_b + root) / a;
		}
		else
		{
			return (false);
		}
		rec->t = t;
		rec->p = at(rec->t, ray);
		rec->normal = mr_vec3_div_double(mr_vec3_sub(rec->p, *center), radius);
		return (true);
	}
	return (false);
}

