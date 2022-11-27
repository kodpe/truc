/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:43:09 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/27 08:59:59 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	mx_hook_key_press(int keycode, t_evstat *ev)
{
	mx_add_key_evstat(ev, MX_EVENT_KEYDOWN, keycode);
	return (0);
}

int	mx_hook_key_release(int keycode, t_evstat *ev)
{
	mx_add_key_evstat(ev, MX_EVENT_KEYUP, keycode);
	return (0);
}

int	mx_hook_mouse_down(int button, int x, int y, t_evstat *ev)
{
	mx_add_mouse_evstat(ev, MX_EVENT_MOUSEDOWM, button, x, y);
	return (0);
}

int	mx_hook_mouse_up(int button, int x, int y, t_evstat *ev)
{
	mx_add_mouse_evstat(ev, MX_EVENT_MOUSEUP, button, x, y);
	return (0);
}

int	mx_hook_mouse_move(int x, int y, t_evstat *ev)
{
	mx_add_mouse_evstat(ev, MX_EVENT_MOUSEMOVE, 0, x, y);
	return (0);
}

int	mx_hook_win_cross(t_evstat *ev)
{
	mx_add_win_cross_evstat(ev);
	return (0);
}

void	mx_hook_init(void *win_ptr, t_evstat *ev)
{
	mlx_hook(win_ptr, MX_EVENT_KEYDOWN, 1L << 0, &mx_hook_key_press, ev);
	mlx_hook(win_ptr, MX_EVENT_KEYUP, 1L << 1, &mx_hook_key_release, ev);
	mlx_hook(win_ptr, MX_EVENT_MOUSEDOWM, 1L << 2, &mx_hook_mouse_down, ev);
	mlx_hook(win_ptr, MX_EVENT_MOUSEUP, 1L << 3, &mx_hook_mouse_up, ev);
	mlx_hook(win_ptr, MX_EVENT_MOUSEMOVE, 1L << 6, &mx_hook_mouse_move, ev);
	mlx_hook(win_ptr, MX_EVENT_WIN_CROSS, 0, &mx_hook_win_cross, ev);
}
