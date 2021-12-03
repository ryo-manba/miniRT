#include "minirt.h"
#include <limits.h>

static t_vec3	at(double t, const t_ray *ray)
{
	return (mr_vec3_add((ray->origin), (mr_vec3_mul_double(ray->direction, t))));
}

static void	hit_cylinder_disc(
	t_element disc,
	const t_ray *ray,
	t_hit_record *rec,
	bool top)
{
	double		h;

	h = disc.height / 2;
	if (!top)
		disc.direction = mr_vec3_mul_double(disc.direction, -1);
	rec->hit = false;
	disc.position = mr_vec3_add(disc.position, mr_vec3_mul_double(disc.direction, h));
	if (rt_hit_plain(&disc, ray, rec))
	{
		if (mr_vec3_length(mr_vec3_sub(rec->p, disc.position)) < disc.diameter / 2)
			rec->hit = true;
	}
	if (!rec->hit)
		rec->p.z = rd_inf(true);
}

bool	hit_at(
	t_element *el,
	double t,
	const t_ray *ray,
	t_hit_record *rec)
{
	rec->t = t;
	rec->p = at(rec->t, ray);
	rec->hit = (rec->p.z >= 0);
	double axial_displacement = mr_vec3_dot(
		mr_vec3_sub(rec->p, el->position), el->direction
	);
	if (fabs(axial_displacement) >= el->height / 2)
		rec->hit = false;
	else
	{
		t_vec3 axial_center = mr_vec3_add(
			el->position,
			mr_vec3_mul_double(
				el->direction,
				axial_displacement
			)
		);
		rec->normal = mr_unit_vector(mr_vec3_sub(rec->p, axial_center));
	}
	return (rec->hit);
}

bool	rt_hit_cylinder(
	t_element *el,
	const t_ray *ray,
	t_hit_record *rec
)
{
	t_hit_record	hits[3];

	ft_bzero(hits, sizeof(t_hit_record) * 3);
	hit_cylinder_disc(*el, ray, &hits[0], true);
	hit_cylinder_disc(*el, ray, &hits[1], false);
	t_vec3 oc = mr_vec3_sub(ray->origin, el->position);
	double oc2 = mr_vec3_dot(oc, oc);
	double b2 = mr_vec3_dot(ray->direction, ray->direction);
	double d2 = mr_vec3_dot(el->direction, el->direction);
	double bd = mr_vec3_dot(ray->direction, el->direction);
	double oc_b = mr_vec3_dot(oc, ray->direction);
	double oc_d = mr_vec3_dot(oc, el->direction);
	double a = b2 * d2 - bd * bd;
	double b = 2 * (oc_b * d2 - oc_d * bd);
	double c = oc2 * d2 - oc_d * oc_d - el->diameter * el->diameter / 4;
	double discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		double root = sqrt(discriminant);
		if (!hit_at(el, (-b - root) / 2 / a, ray, &hits[2])
			&& !hit_at(el, (-b + root) / 2 / a, ray, &hits[2]))
			hits[2].hit = false;
	}
	if (!hits[2].hit)
		hits[2].p.z = rd_inf(true);
	*rec = hits[0];
	if (!rec->hit || (hits[1].hit && hits[1].p.z < rec->p.z))
		*rec = hits[1];
	if (!rec->hit || (hits[2].hit && hits[2].p.z < rec->p.z))
		*rec = hits[2];
	return (rec->hit);
}
