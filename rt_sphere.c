#include "minirt.h"

// 球との衝突判定
double	rt_hit_sphere(const t_vec3 *center, double radius, const t_ray *ray)
{
	const t_vec3	oc = vec3_sub(ray->origin, *center);
	const double	a = vec3_length_squared(ray->direction);
	const double	half_b = vec3_dot(oc, ray->direction);
	const double	c = vec3_length_squared(oc) - radius * radius;
	const double	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
	{
		return (-1.0);
	}
	else
	{
		return (-half_b - sqrt(discriminant) / (2.0 * a));
	}
}
