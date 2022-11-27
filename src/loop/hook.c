/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:43:09 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/27 08:22:14 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	hook_key_press(int keycode, t_game *ga)
{
	mx_add_key_evstat(&ga->evstat, MX_EVENT_KEYDOWN, keycode);
	return (0);
}

int	hook_key_release(int keycode, t_game *ga)
{
	mx_add_key_evstat(&ga->evstat, MX_EVENT_KEYUP, keycode);
	return (0);
}

/* TODO vv*/

int	hook_mouse_down(int button, int x, int y, t_game *ga)
{
	mx_add_mouse_evstat(&ga->evstat, MX_EVENT_MOUSEDOWM, button, x, y);
	return (0);
}

int	hook_mouse_up(int button, int x, int y, t_game *ga)
{
	mx_add_mouse_evstat(&ga->evstat, MX_EVENT_MOUSEUP, button, x, y);
	return (0);
}

int	hook_mouse_move(int x, int y, t_game *ga)
{
	mx_add_mouse_evstat(&ga->evstat, MX_EVENT_MOUSEMOVE, 0, x, y);
	return (0);
}

int	hook_win_cross(t_game *ga)
{
	mx_add_win_cross_evstat(&ga->evstat);
	return (0);
}
