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

static int	_mx_swap_key(int keycode)
{
	if (keycode <= 32 || keycode >= 127) return (keycode);
	if (keycode >= 'A' && keycode <= 'Z') return (keycode + 32);
	if (keycode >= 'a' && keycode <= 'z') return (keycode - 32);
	if (keycode == '`') {return ('~');} if (keycode == '~') {return ('`');}
	if (keycode == '1') {return ('!');} if (keycode == '!') {return ('1');}
	if (keycode == '2') {return ('@');} if (keycode == '@') {return ('2');}
	if (keycode == '3') {return ('#');} if (keycode == '#') {return ('3');}
	if (keycode == '4') {return ('$');} if (keycode == '$') {return ('4');}
	if (keycode == '5') {return ('%');} if (keycode == '%') {return ('5');}
	if (keycode == '6') {return ('^');} if (keycode == '^') {return ('6');}
	if (keycode == '7') {return ('&');} if (keycode == '&') {return ('7');}
	if (keycode == '8') {return ('*');} if (keycode == '*') {return ('8');}
	if (keycode == '9') {return ('(');} if (keycode == '(') {return ('9');}
	if (keycode == '0') {return (')');} if (keycode == ')') {return ('0');}
	if (keycode == '-') {return ('_');} if (keycode == '_') {return ('-');}
	if (keycode == '=') {return ('+');} if (keycode == '+') {return ('=');}
	if (keycode == '\\'){return ('|');} if (keycode == '|') {return ('\\');}
	if (keycode == '[') {return ('{');} if (keycode == '{') {return ('[');}
	if (keycode == ']') {return ('}');} if (keycode == '}') {return (']');}
	if (keycode == '\''){return ('"');} if (keycode == '"') {return ('\'');}
	if (keycode == ';') {return (':');} if (keycode == ':') {return (';');}
	if (keycode == ',') {return ('<');} if (keycode == '<') {return (',');}
	if (keycode == '.') {return ('>');} if (keycode == '>') {return ('.');}
	if (keycode == '/') {return ('?');} if (keycode == '?') {return ('/');}
	return (keycode);
}

static int	_mx_set_key(int event)
{
	if (event == MX_EVENT_KEYDOWN)
		return (1);
	return (0);
}

int	mx_is_ppkey(int keycode)
{
	return (keycode >= 65200 && keycode <= 65599);
}

void	mx_set_ppkey(t_evstat *ev, int event, int keycode) 
{
	if (!mx_is_ppkey(keycode))
		abort();
	if (keycode == KEYCODE_CAPSLOCK)
	{
		if (event == MX_EVENT_KEYDOWN)
		{
			if (ev->key[509] == 1)
				ev->key[509] = 0;
			else
				ev->key[509] = 1;
		}
		return ;
	}
	ev->key[keycode - 65000] = _mx_set_key(event);
}

int	mx_get_ppkey(t_evstat *ev, int keycode)
{
	if (!mx_is_ppkey(keycode))
		abort();
	return (ev->key[keycode - 65000]);
}

char	*mx_get_ppkey_name(int keycode)
{
	if (!mx_is_ppkey(keycode))
		abort();
	if (keycode == KEYCODE_DELETE) return (STR_PPKEY_DELETE);
	if (keycode == KEYCODE_TAB) return (STR_PPKEY_TAB);
	if (keycode == KEYCODE_ENTER) return (STR_PPKEY_ENTER);
	if (keycode == KEYCODE_ESCAPE) return (STR_PPKEY_ESCAPE);
	if (keycode == KEYCODE_LEFT) return (STR_PPKEY_LEFT);
	if (keycode == KEYCODE_UP) return (STR_PPKEY_UP);
	if (keycode == KEYCODE_RIGHT) return (STR_PPKEY_RIGHT);
	if (keycode == KEYCODE_DOWN) return (STR_PPKEY_DOWN);
	if (keycode == KEYCODE_LSHIFT) return (STR_PPKEY_LSHIFT);
	if (keycode == KEYCODE_RSHIFT) return (STR_PPKEY_RSHIFT);
	if (keycode == KEYCODE_LCTRL) return (STR_PPKEY_LCTRL);
	if (keycode == KEYCODE_RCTRL) return (STR_PPKEY_RCTRL);
	if (keycode == KEYCODE_CAPSLOCK) return (STR_PPKEY_CAPSLOCK);
	if (keycode == KEYCODE_LALT) return (STR_PPKEY_LALT);
	if (keycode == KEYCODE_RALTCTRL) return (STR_PPKEY_RALTCTRL);
	return (NULL);
}

void	mx_log_key_evstat(int event, int keycode)
{
	if (!MX_VERBOSE_EVENT)
		return ;
	if (event == MX_EVENT_KEYDOWN)
		fprintf(stderr, "<> %-12s ", STR_KEY_PRESS);
	else
		fprintf(stderr, "<> %-12s ", STR_KEY_RELEASE);
	if (mx_is_ppkey(keycode))
		fprintf(stderr, "[%-5i] [%-9s]\n", keycode, mx_get_ppkey_name(keycode));
	else
		fprintf(stderr, "[%-5i] [%c]\n", keycode, keycode);
}

void	mx_add_key_evstat(t_evstat *ev, int event, int keycode)
{
	ev->mlx_keycode = keycode;
	if ((keycode <= 0 || keycode >= 65600) \
		|| (keycode >= 0 && keycode <= 31) \
		|| (keycode >= 127 && keycode <= 199))
	{
		fprintf(stderr, "\033[0;31m<> %-12s [%i]\033[0m\n", "unknown key", keycode);
		return ;
	}
	if (mx_is_ppkey(keycode))
		mx_set_ppkey(ev, event, keycode);
	if (mx_get_ppkey(ev, KEYCODE_LSHIFT) || mx_get_ppkey(ev, KEYCODE_RSHIFT))
		keycode = _mx_swap_key(keycode);
	if (mx_get_ppkey(ev, KEYCODE_CAPSLOCK))
		keycode = _mx_swap_key(keycode);
	if (keycode >= 32 && keycode <= 126)
		ev->key[keycode] = _mx_set_key(event);
	mx_log_key_evstat(event, keycode);
}

void	mx_log_mouse_evstat(int event, int button, t_2Dpt pos)
{
	if (!MX_VERBOSE_EVENT)
		return ;
	if (event == MX_EVENT_MOUSEDOWM)
		fprintf(stderr, "<> %-12s ", STR_MOUSE_DOWN);
	else if (event == MX_EVENT_MOUSEUP)
		fprintf(stderr, "<> %-12s ", STR_MOUSE_UP);
	else
		fprintf(stderr, "<> %-12s ", STR_MOUSE_MOVE);
	fprintf(stderr, "[%-5i],[%-5i] ", pos.x, pos.y);
	if (button == 0)
		fprintf(stderr, "\n");
	if (button == MOUSE_BUT_LEFT)
		fprintf(stderr, "[BT-L]\n");
	if (button == MOUSE_BUT_MIDDLE)
		fprintf(stderr, "[BT-M]\n");
	if (button == MOUSE_BUT_RIGHT)
		fprintf(stderr, "[BT-R]\n");
	if (button == MOUSE_SCROLL_UP)
		fprintf(stderr, "[SC-U]\n");
	if (button == MOUSE_SCROLL_DOWN)
		fprintf(stderr, "[SC-D]\n");
}

void	mx_add_mouse_evstat(t_evstat *ev, int event, int button, t_2Dpt pos)
{
	ev->mouse[button].event = event;
	ev->mouse[button].pos = pos;
	ev->mouse_event = event;
	ev->mouse_pos = pos;
	mx_log_mouse_evstat(event, button, pos);
	// scroll up / scroll down not work, cf mx_handle_button()
}

void	mx_add_win_cross_evstat(t_evstat *ev)
{
	ev->win_cross = 1;
	fprintf(stderr, "<> %-12s [1]\n", STR_WIN_CROSS);
}
