/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_event.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 03:44:11 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/24 21:27:18 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MX_EVENT_H
# define MX_EVENT_H

# define MOUSE_LEFT			1
# define MOUSE_MIDDLE		2
# define MOUSE_RIGHT		3
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define KEY_ESCAPE	65307
# define KEY_LEFT	65361
# define KEY_UP		65362
# define KEY_RIGHT	65363
# define KEY_DOWN	65364
# define KEY_A		97
# define KEY_D		100
# define KEY_S		115
# define KEY_W		119

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
# define MX_EVENT_CROSSDESTROY	17 /* int (*f)(void *param) */

#endif /* MX_EVENT_H */
