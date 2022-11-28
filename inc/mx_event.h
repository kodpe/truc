/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_event.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 03:44:11 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/28 21:15:07 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MX_EVENT_H
# define MX_EVENT_H

# define MX_VERBOSE_EVENT	0
# define MX_VERBOSE_LOOP	0
# define MX_VERBOSE_BUTTON	1

//mx log event modes
# define STR_WIN_CROSS			"win_cross"
# define STR_KEY_PRESS			"key_press"
# define STR_KEY_RELEASE		"key_release"
# define STR_MOUSE_DOWN			"mouse_down"
# define STR_MOUSE_UP			"mouse_up"
# define STR_MOUSE_MOVE			"mouse"
//mecanic
# define MOUSE_MOVE			0
# define MOUSE_BUT_LEFT		1
# define MOUSE_BUT_MIDDLE	2
# define MOUSE_BUT_RIGHT	3
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

// (0) -> 32 -> 126 -> (200) -> 65200 -> 65600 -> (600)
# define KEYCODE_DELETE		65288
# define KEYCODE_TAB		65289
# define KEYCODE_ENTER		65293
# define KEYCODE_ESCAPE		65307
# define KEYCODE_LEFT		65361
# define KEYCODE_UP			65362
# define KEYCODE_RIGHT		65363
# define KEYCODE_DOWN		65364
# define KEYCODE_LSHIFT		65505
# define KEYCODE_RSHIFT		65506
# define KEYCODE_LCTRL		65507
# define KEYCODE_RCTRL		65508
# define KEYCODE_CAPSLOCK	65509
# define KEYCODE_LALT		65513
# define KEYCODE_RALTCTRL	65514
//
# define STR_PPKEY_DELETE	"DEL"
# define STR_PPKEY_TAB		"TAB"
# define STR_PPKEY_ENTER	"ENT"
# define STR_PPKEY_ESCAPE	"ESC"
# define STR_PPKEY_LEFT		"LEFT"
# define STR_PPKEY_UP		"UP"
# define STR_PPKEY_RIGHT	"RIGHT"
# define STR_PPKEY_DOWN		"DOWN"
# define STR_PPKEY_LSHIFT	"L_SHIFT"
# define STR_PPKEY_RSHIFT	"R_SHIFT"
# define STR_PPKEY_LCTRL	"L_CTRL"
# define STR_PPKEY_RCTRL	"R_CTRL"
# define STR_PPKEY_CAPSLOCK	"CAPSLOCK"
# define STR_PPKEY_LALT		"L_ALT"
# define STR_PPKEY_RALTCTRL	"ALT_CTRL"
///

# define MX_EVENT_KEYDOWN		2 /* int (*f)(int keycode, void *param) */
# define MX_EVENT_KEYUP			3 /* int (*f)(int keycode, void *param) */

# define MX_EVENT_MOUSEDOWM		4 
/* int (*f)(int button, int x, int y, void *param) */
# define MX_EVENT_MOUSEUP		5
/* int (*f)(int button, int x, int y, void *param) */
# define MX_EVENT_MOUSEMOVE		6
/* int (*f)(int x, int y, void *param) */

# define MX_EVENT_ENTERNOTIFY	7
# define MX_EVENT_LEAVENOTIFY	8 

# define MX_EVENT_EXPOSE		12 /* int (*f)(void *param) */
# define MX_EVENT_WIN_CROSS		17 /* int (*f)(void *param) */


#endif /* MX_EVENT_H */
