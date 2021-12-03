#include "minirt.h"
#include <limits.h>

static t_vec3	at(double t, const t_ray *ray)
{
	return (mr_vec3_add((ray->origin), (mr_vec3_mul_double(ray->direction, t))));
}

bool	rt_hit_plain(
	const t_vec3 *center,
	const t_vec3 *normal,
	const t_ray *ray,
	t_hit_record *rec
)
{
	t_vec3 oc = mr_vec3_sub(*center, ray->origin);
	double den = mr_vec3_dot(oc, *normal);
	double num = mr_vec3_dot(ray->direction, *normal);
	if (num == 0)
		return (false);
	double t = den / num;
	rec->t = t;
	rec->p = at(rec->t, ray);
	if (rec->p.z <= 0)
		return (false);
	rec->normal = *normal;
	return (true);
}
