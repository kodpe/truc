/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_event.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 03:44:11 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/26 16:27:00 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MX_EVENT_H
# define MX_EVENT_H

# define MOUSE_LEFT			1
# define MOUSE_MIDDLE		2
# define MOUSE_RIGHT		3
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define KEY_DELETE	65288

# define KEY_ENTER	55293

# define KEY_ESCAPE	65307

# define KEY_LEFT	65361
# define KEY_UP		65362
# define KEY_RIGHT	65363
# define KEY_DOWN	65364

# define KEY_A		97
# define KEY_D		100
# define KEY_S		115
# define KEY_W		119

// struct mv_event_stat
# define KEY_LSHIFT		65505
# define KEY_RSHIFT		65506
# define KEY_LCTRL		65507
# define KEY_RCTRL		65508
# define KEY_CAPSLOCK	65509

# define KEY_LALT		65513
# define KEY_RALTCTRL	65514
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
# define MX_EVENT_CROSSDESTROY	17 /* int (*f)(void *param) */

typedef struct s_event_stat
{
	int	key_delete;

	int	key_enter;

	int	key_escape;

	int	key_lshift;
	int	key_rshift;
	int	key_lctrl;
	int	key_rctrl;
	int	key_capslock;

	int	key_lalt;
	int	key_raltctrl;
}	t_event_stat;

typedef long long	t_time;

typedef struct s_loop
{
	t_time			time_origin;
	t_time			time_elapsed;
	t_time			timeout;
	int				fps;
	t_event_stat	evstat;
}	t_loop;

void	mx_wait_fps(int frame_per_second);
t_time	mx_sc_time_ms(void);
t_time	mx_time_ms(void);
void	mx_loop_time(t_loop *loop);

#endif /* MX_EVENT_H */
