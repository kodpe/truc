/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _mx_maintest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 23:03:15 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/12 01:29:40 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

typedef struct s_mxtest
{
	void	*mlx_ptr;
}	t_mx_test;

#if 1
int	main(void)
{
	t_mx_test	m;

	LOG

	// m.mlx_ptr = mlx_init();
	assert(m.mlx_ptr);
	free(m.mlx_ptr);
	// mx_end_mlx(&m.mlx_ptr);
}
#endif
