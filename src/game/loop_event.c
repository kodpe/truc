/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 06:01:28 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/12 06:53:05 by sloquet          ###   ########.fr       */
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
	exit(0);
	mlx_loop_end(m.)
	return (0);
}

int	hook_key_press(int keycode, void *m)
{
	fprintf(stderr, "key press %i \n", keycode);
	if (keycode == KEY_ESCAPE)
		exit(0);
	return (0);
	(void)m;
}

int	hook_key_release(int keycode, void *m)
{
	fprintf(stderr, "key release %i \n", keycode);
	return (0);
	(void)m;
}

int	hook_mouse_move(int button, int x, int y, void *m)
{
	fprintf(stderr, "mouse [%i, %i]\n", x, y);
	return (0);
	(void)m;
}

#if 0
void	main_loop(void *m)
{
	// mlx_loop_hook(m->mlx.ptr, &hook_chrono, m);
	mlx_hook(m->mlx.win.ptr, MX_EVENT_KEYDOWN,		0, &hook_key_press, m);
	mlx_hook(m->mlx.win.ptr, MX_EVENT_KEYUP, 		0, &hook_key_release, m);
	mlx_hook(m->mlx.win.ptr, MX_EVENT_MOUSEMOVE,	0, &hook_mouse_move, m);
	mlx_hook(m->mlx.win.ptr, MX_EVENT_CROSSDESTROY,	0, &hook_crossdestroy, m);
	mlx_loop(m->mlx.ptr);
}
#endif
