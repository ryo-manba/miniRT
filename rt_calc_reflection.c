/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_calc_reflection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:49 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/12/12 19:24:03 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	mr_vec3_mul(const t_vec3 *u, const t_vec3 *v)
{
	t_vec3	mul;

	mul.x = u->x * v->x;
	mul.y = u->y * v->y;
	mul.z = u->z * v->z;
	return (mul);
}

// 環境光
t_vec3 rt_ambient(
	const double ratio,
	const t_vec3 *ambient_color,
	const t_vec3 *obj_color)
{
	t_vec3	ambient = mr_vec3_mul_double(ambient_color, ratio);
	return (mr_vec3_mul(&ambient, obj_color)); // 環境光(rgb * 輝度) * 物体の色
}

// 光源の強さ * cosθ
t_vec3	rt_diffuse(
	const t_hit_record *rec,
	const t_vec3 *light_p,
	const t_vec3 *light_color,
	const t_ray *ray)
{
	if (!rec->hit)
		return ((t_vec3){0, 0, 0});
	t_vec3 c;
	t_vec3 temp = mr_vec3_sub(rec->p, *light_p); // 光の入射ベクトル
	t_vec3 light_in = mr_unit_vector(&temp);
	t_vec3 normal = rec->normal;
	t_vec3 ray_in = mr_unit_vector(&ray->direction);
	double cos_light = mr_vec3_dot(light_in, normal); // 入射ベクトルと法線ベクトルのなす角
	double cos_ray = mr_vec3_dot(ray_in, normal); // レイベクトルと法線ベクトルのなす角
	if (cos_light * cos_ray <= 0) // 光源とカメラが反射面を挟んで逆側にいる時反射は起きない
		return ((t_vec3){0, 0, 0});
	double r_light = mr_vec3_length(&temp);
	double ratio = 1;
	double x = fabs(cos_light * ratio / r_light / r_light);
	// 点光源から面に到達する光束は、点光源と面の距離の二乗に反比例する
	c = mr_vec3_mul_double(light_color, x);
	return (c);
}

t_vec3	rt_specular(
	const t_hit_record *rec,
	const t_vec3 *light,
	const t_vec3 *light_color,
	const t_ray *ray)
{
	const double	k = 0.3; // 鏡面反射係数
	const double	i = 1.0; // 光源の光の強度
//	const double	a = 30.0; // 光沢度
	const double	a = 30.0; // 光沢度

	if (!rec->hit)
		return ((t_vec3){0, 0, 0});
	const t_vec3	tmp = mr_vec3_mul_double(&ray->direction, -1);
	const t_vec3	v = mr_unit_vector(&tmp); // 視線ベクトルの逆ベクトル
	const t_vec3	tmp2 = mr_vec3_sub(*light, rec->p);
	const t_vec3	l = mr_unit_vector(&tmp2); // 光の入射方向ベクトル

	// 𝐫⃗ = 2(𝐧⃗ ⋅ℓ⃗ )𝐧⃗ −ℓ⃗
	const t_vec3	n = mr_unit_vector(&rec->normal); // 物体面の法線ベクトル
	const t_vec3	r = mr_vec3_sub(mr_vec3_mul_double(&n, mr_vec3_dot(n, l) * 2), l); // 入射光の正反射ベクトル

	if (mr_vec3_dot(n, l) < 0 || mr_vec3_dot(v, r) < 0)
		return ((t_vec3){0, 0, 0});

	// 𝑅𝑠=𝑘𝑠𝐼𝑖(𝐯⃗ ⋅𝐫⃗ )^𝛼
	t_vec3 x = mr_vec3_mul_double(light_color, (k * i * pow(mr_vec3_dot(v, r), a))); // 直接光の鏡面反射光の放射輝度
	return (x);
}
