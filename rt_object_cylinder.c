#include "minirt.h"

static void	hit_cylinder_disc(
	const t_element *cylinder,
	const t_ray *ray,
	t_hit_record *rec,
	bool top)
{
	double		h;
	t_vec3		temp;
	t_element	disc;

	ft_memcpy(&disc, cylinder, sizeof(t_element));
	h = disc.height / 2;
	if (!top)
		disc.direction = mr_vec3_mul_double(&disc.direction, -1);
	rec->hit = false;
	disc.position = mr_vec3_add(disc.position, mr_vec3_mul_double(&disc.direction, h));
	if (rt_hittest_plane(&disc, ray, rec))
	{
		temp = mr_vec3_sub(rec->p, disc.position);
		if (mr_vec3_length(&temp) < disc.diameter / 2)
			rec->hit = true;
	}
	rt_after_hit(&disc, ray, rec);
}

static bool	hit_at(
	const t_element *el,
	double t,
	const t_ray *ray,
	t_hit_record *rec)
{
	rec->t = t;
	
	rec->p = rt_hit_point(rec->t, ray);
	rec->hit = (rec->t >= 1);
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
				&el->direction,
				axial_displacement
			)
		);
		t_vec3	temp;
		temp = mr_vec3_sub(rec->p, axial_center);
		rec->normal = mr_unit_vector(&temp);
		rt_after_hit(el, ray, rec);
	}
	return (rec->hit);
}

static void	hit_cylinder_side(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
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
	if (discriminant < 0)
		return ;
	double root = sqrt(discriminant);
	if (!hit_at(el, (-b - root) / 2 / a, ray, rec)
		&& !hit_at(el, (-b + root) / 2 / a, ray, rec))
		rec->hit = false;
}

bool	rt_hittest_cylinder(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	t_hit_record	hits[3];

	ft_bzero(hits, sizeof(t_hit_record) * 3);
	hit_cylinder_disc(el, ray, &hits[0], true);
	hit_cylinder_disc(el, ray, &hits[1], false);
	hit_cylinder_side(el, ray, &hits[2]);
	hits[0].color = (t_vec3){ 1, 0, 1 };
	hits[1].color = (t_vec3){ 1, 1, 0 };
	*rec = hits[0];
	if (!rec->hit || (hits[1].hit && hits[1].t < rec->t))
		*rec = hits[1];
	if (!rec->hit || (hits[2].hit && hits[2].t < rec->t))
		*rec = hits[2];
	return (rec->hit);
}
