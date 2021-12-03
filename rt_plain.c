#include "minirt.h"
#include <limits.h>

static t_vec3	at(double t, const t_ray *ray)
{
	return (mr_vec3_add((ray->origin), (mr_vec3_mul_double(ray->direction, t))));
}

bool	rt_hit_plain(
	t_element *el,
	const t_ray *ray,
	t_hit_record *rec
)
{
	t_vec3 oc = mr_vec3_sub(el->position, ray->origin);
	double den = mr_vec3_dot(oc, el->direction);
	double num = mr_vec3_dot(ray->direction, el->direction);
	if (num == 0)
		return (false);
	double t = den / num;
	rec->t = t;
	rec->p = at(rec->t, ray);
	if (rec->p.z <= 0)
		return (false);
	rec->normal = el->direction;
	return (true);
}
