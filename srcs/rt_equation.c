/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_equation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 17:01:33 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/12 02:02:22 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define EPS 1e-6

// solve a given linear equation 2 * b_half * t + c = 0,
// and returns the number of the equation.
int	rt_solve_equation1(t_equation2 *arg)
{
	if (fabs(arg->b_half) < EPS)
		arg->solutions = 0;
	else
	{
		arg->solutions = 1;
		arg->t1 = -arg->c / (2 * arg->b_half);
	}
	return (arg->solutions);
}

// solve a given quadratic equation a * t^2 + 2 * b_half * t + c = 0,
// and returns the number of the equation.
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
		if (arg->a > 0)
		{
			arg->t1 = (-arg->b_half - sqrt(discriminant)) / arg->a;
			arg->t2 = (-arg->b_half + sqrt(discriminant)) / arg->a;
		}
		else
		{
			arg->t2 = (-arg->b_half - sqrt(discriminant)) / arg->a;
			arg->t1 = (-arg->b_half + sqrt(discriminant)) / arg->a;
		}
	}
	return (arg->solutions);
}
