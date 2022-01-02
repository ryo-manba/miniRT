/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tangent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 13:52:57 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/02 18:19:55 by corvvs           ###   ########.fr       */
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
	const double u = rec->u;
	const double v = rec->v;
	const double m_freq = 10; // 周波数; 1周当たりのブロック数
	const int sines = (int)(floor(m_freq * u) + floor(m_freq * v));

	if (sines % 2 == 0)
	{
		t_vec3 odd = _GREEN;
		mr_normalize_color(&odd);
		return (odd);
	}
	else
	{
		t_vec3 even = _BLACK;
		mr_normalize_color(&even);
		return (even);
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
	if (rec->element.bumpmap)
		rec->normal = test_bumpfunc_image(rec->u, rec->v, rec->element.bumpmap);
	else
		rec->normal = Z0;
	rec->normal = rt_vec_tangent_to_global(rec, &rec->normal);
	// 色ベクトル
	// テクスチャマップがある場合はそれをみる。
	// チェッカーを使う場合はチェッカーに従って計算。
	// どちらでもない場合はelementの色を使う。
	if (rec->element.textype == RD_TT_TEXMAP && rec->element.texture)
		rec->color = rt_element_color(rec->u, rec->v, &rec->element);
	else if (rec->element.textype == RD_TT_CHECKER)
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
