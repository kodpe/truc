/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 06:01:28 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/12 18:08:40 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

#define KEY_ESCAPE	65307
#define KEY_LEFT	65361
#define KEY_UP		65362
#define KEY_RIGHT	65363
#define KEY_DOWN	65364
#define KEY_A		97
#define KEY_D		100
#define KEY_S		115
#define KEY_W		119

#define MX_EVENT_KEYDOWN		2 /* int (*f)(int keycode, void *param) */
#define MX_EVENT_KEYUP			3 /* int (*f)(int keycode, void *param) */

#define MX_EVENT_MOUSEDOWM		4 
/* int (*f)(int button, int x, int y, void *param) */
#define MX_EVENT_MOUSEUP		5
/* int (*f)(int button, int x, int y, void *param) */
#define MX_EVENT_MOUSEMOVE		6
/* int (*f)(int x, int y, void *param) */

#define MX_EVENT_ENTERNOTIFY	7
#define MX_EVENT_LEAVENOTIFY	8 

#define MX_EVENT_EXPOSE			12 /* int (*f)(void *param) */
#define MX_EVENT_CROSSDESTROY	17 /* int (*f)(void *param) */

int	hook_crossdestroy(t_test *m)
{
	mlx_loop_end(m->mlx_ptr);
	return (0);
}

int	hook_key_press(int keycode, t_test *m)
{
	fprintf(stderr, "<> key press   [%i] [%c]\n", keycode, keycode);
	if (keycode == KEY_ESCAPE)
		mlx_loop_end(m->mlx_ptr);
	return (0);
}

int	hook_key_release(int keycode, t_test *m)
{
	fprintf(stderr, "<> key release [%i] [%c]\n", keycode, keycode);
	return (0);
	(void)m;
}

int	hook_mouse_down(int button, int x, int y, t_test *m)
{
	fprintf(stderr, "<> mouse down  [%i] [%i],[%i]\n", button, x, y);
	return (0);
	(void)m;
}

int	hook_mouse_up(int button, int x, int y, t_test *m)
{
	fprintf(stderr, "<> mouse up    [%i] [%i],[%i]\n", button, x, y);
	return (0);
	(void)m;
}

int	hook_mouse_move(int x, int y, t_test *m)
{
	fprintf(stderr, "<> mouse move  [%i],[%i]\n", x, y);
	return (0);
	(void)m;
}
int	hook_frame(t_test *m)
{
	sleep(0.1);
	return (0);
	(void)m;
}

#if 1
void	main_loop(t_test *m)
{
	mlx_loop_hook(m->mlx_ptr, &hook_frame, m);
	mlx_hook(m->win.ptr, MX_EVENT_KEYDOWN, 1L << 0, &hook_key_press, m);
	mlx_hook(m->win.ptr, MX_EVENT_KEYUP, 1L << 1, &hook_key_release, m);
	mlx_hook(m->win.ptr, MX_EVENT_MOUSEDOWM, 1L << 2, &hook_mouse_down, m);
	mlx_hook(m->win.ptr, MX_EVENT_MOUSEUP, 1L << 3, &hook_mouse_up, m);
	mlx_hook(m->win.ptr, MX_EVENT_MOUSEMOVE, 1L << 6, &hook_mouse_move, m);
	mlx_hook(m->win.ptr, MX_EVENT_CROSSDESTROY,	0, &hook_crossdestroy, m);
	mlx_loop(m->mlx_ptr);
	return ;
}
#endif
