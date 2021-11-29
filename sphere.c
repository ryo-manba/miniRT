#include "minirt.h"

// 球との衝突判定
bool	hit_sphere(const t_vec3 *center, double radius, const t_ray *ray)
{
	const t_vec3	oc = vec3_sub(ray->origin, *center);
	const double	a = vec3_dot(ray->direction, ray->direction);
	const double	b = 2.0 * vec3_dot(oc, ray->direction);
	const double	c = vec3_dot(oc, oc) - radius * radius;
	const double	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}
