#include "minirt.h"
#include <limits.h>

#define EPS 1e-8

bool	rt_hittest_sphere(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	const t_vec3	oc = mr_vec3_sub(ray->origin, el->position);
	const double	a = mr_vec3_length_squared(&ray->direction);
	const double	half_b = mr_vec3_dot(oc, ray->direction);
	const double	c = mr_vec3_length_squared(&oc) - el->radius * el->radius;
	const double	discriminant = half_b * half_b - a * c;

	if (discriminant >= 0) // 交差判定
	{
		double root = sqrt(discriminant);
		double t = 0;
		if (((-half_b - root) / a) >= 1)
		{
			t = (-half_b - root) / a;
		}
		else if (((-half_b + root) / a) >= 1)
		{
			t = (-half_b + root) / a;
		}
		else
		{
			return (false);
		}
		rec->t = t;
		rec->p = rt_hit_point(rec->t, ray);
		t_vec3	temp;
		temp = mr_vec3_sub(rec->p, el->position);
		rec->normal = mr_vec3_div_double(&temp, el->radius);
		rec->cos = mr_vec3_dot(mr_unit_vector(&ray->direction), rec->normal);
		rec->color = el->color;
		return (true);
	}
	return (false);
}

