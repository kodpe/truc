/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_event.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 03:44:11 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/26 18:42:46 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MX_EVENT_H
# define MX_EVENT_H

# define MX_VERBOSE_EVENT	1

//mx log event modes
# define WIN_CROSS			"win exit_cross"
# define KEY_PRESS			"key press"
# define KEY_RELEASE		"key release"
//
# define K_PRESS			'p'
# define K_RELEASE			'r'

# define MOUSE_LEFT			1
# define MOUSE_MIDDLE		2
# define MOUSE_RIGHT		3
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5


# define KEY_SPACE	32

# define KEY_A		97
# define KEY_D		100
# define KEY_S		115
# define KEY_W		119

# define KEY_DELETE		65288
# define KEY_TAB		65289

# define KEY_ENTER		65293

# define KEY_ESCAPE		65307

# define KEY_LEFT		65361
# define KEY_UP			65362
# define KEY_RIGHT		65363
# define KEY_DOWN		65364

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
# define MX_EVENT_WIN_CROSS		17 /* int (*f)(void *param) */

typedef struct s_event_stat
{
	int	mlx_keycode;

	int	key_space;

	int	key_tab;

	int	key_delete;

	int	key_enter;

	int	key_escape;

	int	key_arrow_left;
	int	key_arrow_up;
	int key_arrow_right;
	int key_arrow_down;

	int	key_lshift;
	int	key_rshift;
	int	key_lctrl;
	int	key_rctrl;
	int	key_capslock;

	// int	key_lalt;
	// int	key_raltctrl;

	int	win_exit_cross;
}	t_event_stat;
// TODO add more keys
//TODO tableau pour les keys avec defines et bon index directement

void	mx_add_keycode_to_evstat(t_event_stat *evstat, char *mode, int keycode);
void	mx_log_event(char *mode, int keycode);

typedef long long	t_time;

typedef struct s_loop
{
	int				active;
	int				last_loop_id;
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
