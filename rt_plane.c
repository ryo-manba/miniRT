#include "minirt.h"
#include <limits.h>

bool	rt_hit_plane(
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
	rec->p = rt_hit_point(rec->t, ray);
	if (rec->t < 1)
		return (false);
	rec->normal = el->direction;
	rec->cos = mr_vec3_dot(mr_unit_vector(&ray->direction), rec->normal);
	rec->color = el->color;
	return (true);
}
