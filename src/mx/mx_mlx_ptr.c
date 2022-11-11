/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_mlx_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:29:15 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/11 23:38:59 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

#undef MX_NAME
#define MX_NAME "mx_init_mlx()"

int	mx_init_mlx(void *mlx_ptr)
{
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	mx_log_ptr(MX_NAME, mlx_ptr);
	return (0);
}

#undef MX_NAME
#define MX_NAME "mx_end_mlx()"

void	mx_end_mlx(void *mlx_ptr)
{
	mx_log_ptr(MX_NAME, mlx_ptr);
	free(mlx_ptr);
	mlx_ptr = NULL;
}
