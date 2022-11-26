/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:13:34 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/25 22:39:02 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

#undef MX_NAME
#define MX_NAME "mx_init_win()"

t_win	mx_init_win(void *mlx_ptr, int width, int height, int x, int y)
{
	t_win	win;

	ft_memset(&win, 0, sizeof(t_win));
	win.width = width;
	win.height = height;
	win.x = x;
	win.y = y;
	win.mlx_ptr = mlx_ptr;
	mx_log_win(MX_NAME, &win);
	return (win);
}

#undef MX_NAME
#define MX_NAME "mx_create_win()"

int	mx_create_win(t_win *win, char *name)
{
	if (win->width < 100 || win->height < 100)
		return (1);
	win->name = ft_strdup(name);
	if (!win->name)
		return (1);
	win->ptr = mlx_new_window_pos(win->mlx_ptr, \
		win->width, win->height, win->name, win->x, win->y);
	if (!win->ptr)
		return (1);
	win->box = mx_aabb(mx_pt(0, 0), mx_vec(win->width, win->height));
	mx_log_win(MX_NAME, win);
	return (0);
}

#undef MX_NAME
#define MX_NAME "mx_destroy_win()"

void	mx_destroy_win(t_win *win)
{
	mx_log_win(MX_NAME, win);
	if (win == NULL)
		return ;
	if (win->ptr)
		mlx_destroy_window(win->mlx_ptr, win->ptr);
	if (win->name)
		free(win->name);
	ft_memset(win, 0, sizeof(t_win));
}
