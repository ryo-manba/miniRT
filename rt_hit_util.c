#include "minirt.h"

t_vec3	rt_hit_point(double t, const t_ray *ray)
{
	return (mr_vec3_add((ray->origin), (mr_vec3_mul_double(&ray->direction, t))));
}
