/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tangent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 13:52:57 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/05 00:11:48 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_object_tangent_setter g_tangent_setters[] = {
	NULL,
	NULL,
	NULL,
	NULL,
	rt_set_tangent_sphere,
	rt_set_tangent_plane,
	rt_set_tangent_cylinder,
	rt_set_tangent_cone,
};

/** m_freq:
 *  plane    :  0.5
 *  cylinder : 10.0
 *  sphere   : 10.0
 */ 
static t_vec3	checker_texture(const t_hit_record *rec)
{
	const double	u = rec->u;
	const double	v = rec->v;
	const t_element	*el = rec->element.tex_el;
	const int sines = (int)(floor(el->freq_u * u) + floor(el->freq_v * v));

	if (sines % 2 == 0)
	{
		return (el->color);
	}
	else
	{
		return (el->subcolor);
	}
}

void	rt_set_tangent_space(
	t_hit_record *rec
)
{
	g_tangent_setters[rec->element.etype](rec);
	// 法線ベクトル
	// バンプマップがある場合はそれをみる。
	// ない場合は(0,0,1)を接空間から通常空間に逆変換する。
	if (rec->element.bump_el && rec->element.bump_el->image)
		rec->normal = test_bumpfunc_image(rec->u, rec->v, rec->element.bump_el->image);
	else
		rec->normal = Z0;
	rec->normal = rt_vec_tangent_to_global(rec, &rec->normal);
	// 色ベクトル
	// テクスチャマップがある場合はそれをみる。
	// チェッカーを使う場合はチェッカーに従って計算。
	// どちらでもない場合はelementの色を使う。
	if (rec->element.tex_el && rec->element.tex_el->etype == RD_ET_TEXTURE)
		rec->color = rt_element_color(rec->u, rec->v, &rec->element);
	else if (rec->element.tex_el && rec->element.tex_el->etype == RD_ET_CHECKER)
		rec->color = checker_texture(rec);
	else
		rec->color = rec->element.color;
}

// 接空間上のベクトルを通常空間に変換する
t_vec3	rt_vec_tangent_to_global(
	t_hit_record *rec,
	t_vec3 *vtangent
)
{
	t_vec3	vglobal;

	vglobal.x = rec->u0.x * vtangent->x
		+ rec->v0.x * vtangent->y
		+ rec->w0.x * vtangent->z;
	vglobal.y = rec->u0.y * vtangent->x
		+ rec->v0.y * vtangent->y
		+ rec->w0.y * vtangent->z;
	vglobal.z = rec->u0.z * vtangent->x
		+ rec->v0.z * vtangent->y
		+ rec->w0.z * vtangent->z;
	return (vglobal);
}
