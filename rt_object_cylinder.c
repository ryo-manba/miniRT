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
		rec->hit = (mr_vec3_length(&temp) < disc.diameter / 2);
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
	double axial_displacement = mr_vec3_dot(
		mr_vec3_sub(rec->p, el->position), el->direction
	);
	if (t < 1 || fabs(axial_displacement) >= el->height / 2)
		rec->hit = false;
	else
	{
		rec->hit = true;
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

static void	rt_texture_cylinder(t_hit_record *rec, const t_element *el, const t_ray *ray)
{
//	double tmp = mr_vec3_dot(mr_vec3_sub(ray->origin, el->position), el->direction);
//	t_vec3 f = mr_vec3_add(mr_vec3_mul_double(&el->direction, tmp), el->position);

//	t_vec3 tmp2 = mr_vec3_sub(ray->origin, f);
//	t_vec3 dx = mr_vec3_div_double(&tmp2, mr_vec3_length_squared(&tmp2));

	(void)ray;
	t_vec3 vecx = {1, 0, 0};
	t_vec3 vecy = {0, 1, 0};
	t_vec3 vecz = {0, 0, 1};

	t_vec3 r;

	if (el->direction.y != 0 || el->direction.z != 0) r = vecx;
	if (el->direction.z != 0 || el->direction.x != 0) r = vecy;
	if (el->direction.x != 0 || el->direction.y != 0) r = vecz;

	t_vec3 dx = mr_vec3_cross(&el->direction, &r);

	dx = mr_unit_vector(&dx);
//	vec3_debug(&dx);
//	t_vec3 dx = mr_vec3_div_double(&tmp2, mr_vec3_length_squared(&tmp2));

	t_vec3 tmp3 = mr_vec3_mul_double(&el->direction, mr_vec3_dot(el->direction, dx));
	t_vec3 dz = mr_vec3_add(tmp3, mr_vec3_cross(&el->direction, &dx));

	double x = mr_vec3_dot(mr_vec3_sub(rec->p, el->position), dx);
	double z = mr_vec3_dot(mr_vec3_sub(rec->p, el->position), dz);

	double theta = atan2(x, z);
	// x = (衝突点 - 円柱の円柱の中心位置ベクトル) ･ 円柱の中心軸の方向ベクトル
	double a = mr_vec3_dot(mr_vec3_sub(rec->p, el->position), el->direction);

	// a = (-h/2 ~h/2)
//	mr_vec3_sub(ray->origin, f);

	// 仰角
	double phi = a * M_PI / el->height;
	rec->tex.u = theta / M_PI;
	rec->tex.v = phi / M_PI;
//	printf("%f %f %f\n", x, rec->tex.u, rec->tex.v);
}


bool	rt_hittest_cylinder(
	const t_element *el,
	const t_ray *ray,
	t_hit_record *rec)
{
	t_hit_record	hits[3];
	t_hit_record	*h;

	ft_bzero(hits, sizeof(t_hit_record) * 3);
	hit_cylinder_disc(el, ray, &hits[0], true);
	hit_cylinder_disc(el, ray, &hits[1], false);
	hit_cylinder_side(el, ray, &hits[2]);
	h = NULL;
	if (hits[0].hit)
		h = &hits[0];
	if (hits[1].hit && (!h || !h->hit || hits[1].t < h->t))
		h = &hits[1];
	if (hits[2].hit && (!h || !h->hit || hits[2].t < h->t))
		h = &hits[2];
	if (h)
		*rec = *h;

	// !!BONUS
	rt_texture_cylinder(rec, el, ray);
	return (!!h);
}
