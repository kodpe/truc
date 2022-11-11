/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_vec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:34:31 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/11 15:03:29 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

t_2Dvec	mx_vec(int x, int y)
{
	t_2Dvec	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_2Dpt	mx_pt_add_vec(t_2Dpt pt, t_2Dvec vec)
{
	t_2Dpt	new_pt;

	new_pt.x = pt.x + vec.x;
	new_pt.y = pt.y + vec.y;
	return (new_pt);
}

t_2Dpt	mx_pt_sub_vec(t_2Dpt pt, t_2Dvec vec)
{
	t_2Dpt	new_pt;

	new_pt.x = pt.x - vec.x;
	new_pt.y = pt.y - vec.y;
	return (new_pt);
}

t_2Dvec	mx_vec_add_vec(t_2Dvec vec_a, t_2Dvec vec_b)
{
	t_2Dvec	new_vec;

	new_vec.x = vec_a.x + vec_b.x;
	new_vec.y = vec_a.y + vec_b.y;
	return (new_vec);
}

t_2Dvec	mx_vec_sub_vec(t_2Dvec vec_a, t_2Dvec vec_b)
{
	t_2Dvec	new_vec;

	new_vec.x = vec_a.x - vec_b.x;
	new_vec.y = vec_a.y - vec_b.y;
	return (new_vec);
}

t_2Dvec	mx_mul_vec(t_2Dvec vec, int scalar)
{
	t_2Dvec	new_vec;

	new_vec.x = vec.x * scalar;
	new_vec.y = vec.y * scalar;
	return (new_vec);
}

t_2Dvec	mx_div_vec(t_2Dvec vec, int scalar)
{
	t_2Dvec	new_vec;

	if (scalar == 0)
		abort();
	new_vec.x = vec.x / scalar;
	new_vec.y = vec.y / scalar;
	return (new_vec);
}

bool	mx_same_vec(t_2Dvec vec_a, t_2Dvec vec_b)
{
	return (vec_a.x == vec_b.x && vec_a.y == vec_b.y);
}
