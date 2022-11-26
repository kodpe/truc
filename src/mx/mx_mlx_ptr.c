/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_mlx_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:29:15 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/25 22:39:21 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

#undef MX_NAME
#define MX_NAME "mx_init_mlx()"

void	*mx_init_mlx(void)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (NULL);
	mx_log_ptr(MX_NAME, mlx_ptr);
	return (mlx_ptr);
}

#undef MX_NAME
#define MX_NAME "mx_destroy_mlx()"

void	mx_destroy_mlx(void *mlx_ptr)
{
	mx_log_ptr(MX_NAME, mlx_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	mlx_ptr = NULL;
}
