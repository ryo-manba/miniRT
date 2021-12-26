/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_equation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 17:01:33 by corvvs            #+#    #+#             */
/*   Updated: 2021/12/25 17:19:02 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define EPS 1e-6

// arg で定義される1次方程式 2b_half t + c = 0 を解き、答えの数(0, 1)を返す。
int	rt_solve_equation1(t_equation2 *arg)
{
	if (fabs(arg->b_half) < EPS)
		arg->solutions = 0;
	else
	{
		arg->solutions = 1;
		arg->t1 = - arg->c / (2 * arg->b_half);
	}
	return (arg->solutions);
}

// arg で定義される2次方程式 at^2 + 2b_half t + c = 0 を解き、答えの数(0, 1, 2)を返す。
int	rt_solve_equation2(t_equation2 *arg)
{
	const double	discriminant = arg->b_half * arg->b_half - arg->a * arg->c;

	if (fabs(arg->a) < EPS)
		return (rt_solve_equation1(arg));
	if (discriminant < 0)
		arg->solutions = 0;
	else
	{
		arg->solutions = 2;
		arg->t1 = (-arg->b_half - sqrt(discriminant)) / arg->a;
		arg->t2 = (-arg->b_half + sqrt(discriminant)) / arg->a;
	}
	return (arg->solutions);
}
