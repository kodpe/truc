/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_add_evstat_keycode.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:24:54 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/26 18:39:36by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

void	mx_log_event(char *mode, int keycode)
{
	if (!MX_VERBOSE_EVENT)
		return ;

	if (keycode == KEY_SPACE)
		fprintf(stderr, "<> %16s [%i] [SPACE]\n", mode, keycode);

	else if (keycode == KEY_DELETE)
		fprintf(stderr, "<> %16s [%i] [DELETE]\n", mode, keycode);
	else if (keycode == KEY_TAB)
		fprintf(stderr, "<> %16s [%i] [TAB]\n", mode, keycode);

	else if (keycode == KEY_ENTER)
		fprintf(stderr, "<> %16s [%i] [ENTER]\n", mode, keycode);

	else if (keycode == KEY_ESCAPE)
		fprintf(stderr, "<> %16s [%i] [ESCAPE]\n", mode, keycode);

	else if (keycode == KEY_LEFT)
		fprintf(stderr, "<> %16s [%i] [ARROW_LEFT]\n", mode, keycode);
	else if (keycode == KEY_UP)
		fprintf(stderr, "<> %16s [%i] [ARROW_UP]\n", mode, keycode);
	else if (keycode == KEY_RIGHT)
		fprintf(stderr, "<> %16s [%i] [ARROW_RIGHT]\n", mode, keycode);
	else if (keycode == KEY_DOWN)
		fprintf(stderr, "<> %16s [%i] [ARROW_DOWN]\n", mode, keycode);

	else if (keycode == KEY_LSHIFT)
		fprintf(stderr, "<> %16s [%i] [LSHIFT]\n", mode, keycode);
	else if (keycode == KEY_RSHIFT)
		fprintf(stderr, "<> %16s [%i] [RSHIFT]\n", mode, keycode);
	else if (keycode == KEY_LCTRL)
		fprintf(stderr, "<> %16s [%i] [LCTRL]\n", mode, keycode);
	else if (keycode == KEY_RCTRL)
		fprintf(stderr, "<> %16s [%i] [RCTRL]\n", mode, keycode);
	else if (keycode == KEY_CAPSLOCK)
		fprintf(stderr, "<> %16s [%i] [CAPSLOCK]\n", mode, keycode);

	else
		fprintf(stderr, "<> %16s [%i] [%c]\n", mode, keycode, keycode);
}

void	mx_add_keycode_to_evstat(t_event_stat *evstat, char *mode, int keycode)
{
	evstat->mlx_keycode = keycode;

	if (keycode == KEY_SPACE)
		evstat->key_space = 1;

	if (keycode == KEY_TAB)
		evstat->key_tab = 1;

	if (keycode == KEY_DELETE)
		evstat->key_delete = 1;

	if (keycode == KEY_ENTER)
		evstat->key_enter = 1;

	if (keycode == KEY_ESCAPE)
		evstat->key_escape = 1;

	if (keycode == KEY_LEFT)
		evstat->key_arrow_left = 1;
	if (keycode == KEY_UP)
		evstat->key_arrow_up = 1;
	if (keycode == KEY_RIGHT)
		evstat->key_arrow_right= 1;
	if (keycode == KEY_DOWN)
		evstat->key_arrow_down = 1;

	if (keycode == KEY_LSHIFT)
	{
		if (mode[4] == K_PRESS)
			evstat->key_lshift = 1;
		if (mode[4] == K_RELEASE)
			evstat->key_lshift = 0;
	}

	if (keycode == KEY_RSHIFT)
	{
		if (mode[4] == K_PRESS)
			evstat->key_rshift = 1;
		if (mode[4] == K_RELEASE)
			evstat->key_rshift = 0;
	}

	if (keycode == KEY_LCTRL)
	{
		if (mode[4] == K_PRESS)
			evstat->key_lctrl = 1;
		if (mode[4] == K_RELEASE)
			evstat->key_lctrl = 0;
	}

	if (keycode == KEY_RCTRL)
	{
		if (mode[4] == K_PRESS)
			evstat->key_rctrl = 1;
		if (mode[4] == K_RELEASE)
			evstat->key_rctrl = 0;
	}

	if (keycode == KEY_CAPSLOCK && mode[4] == K_PRESS)
	{
		if (evstat->key_capslock)
			evstat->key_capslock = 0;
		else
			evstat->key_capslock = 1;
	}

	if (ft_isalpha(keycode))
	{
		if (evstat->key_lshift || evstat->key_rshift)
		{
			if (evstat->key_capslock == 0)
				keycode = ft_toupper(keycode);
		}
		else
		{
			if (evstat->key_capslock)
				keycode = ft_toupper(keycode);
		}
	}

	mx_log_event(mode, keycode);
}
