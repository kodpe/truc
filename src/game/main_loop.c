/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 06:01:28 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/24 20:56:36 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

#define MOUSE_LEFT			1
#define MOUSE_MIDDLE		2
#define MOUSE_RIGHT			3
#define MOUSE_SCROLL_UP		4
#define MOUSE_SCROLL_DOWN	5

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

int	hook_crossdestroy(t_game *ga)
{
	mlx_loop_end(ga->mlx_ptr);
	return (0);
}

int	hook_key_press(int keycode, t_game *ga)
{
	fprintf(stderr, "<> key press   [%i] [%c]\n", keycode, keycode);
	if (keycode == KEY_ESCAPE)
		mlx_loop_end(ga->mlx_ptr);
	return (0);
}

int	hook_key_release(int keycode, t_game *ga)
{
	fprintf(stderr, "<> key release [%i] [%c]\n", keycode, keycode);
	return (0);
	(void)ga;
}

int	hook_mouse_down(int button, int x, int y, t_game *ga)
{
	fprintf(stderr, "<> mouse down  [%i] [%i],[%i]\n", button, x, y);

	if (button == MOUSE_LEFT && mx_coll_xy_aabb(x, y, ga->xpm[3].box_abs))
	{
		mx_draw_aabb(&ga->xpm[3], ga->xpm[3].box_rel, RED);
		mx_draw_img(&ga->xpm[3]);
	}

	return (0);
	(void)ga;
}

int	hook_mouse_up(int button, int x, int y, t_game *ga)
{
	fprintf(stderr, "<> mouse up    [%i] [%i],[%i]\n", button, x, y);

	if (button == MOUSE_LEFT && mx_coll_xy_aabb(x, y, ga->xpm[3].box_abs))
	{
		mx_fill_img(&ga->xpm[3], LIME);
		mx_draw_aabb(&ga->xpm[3], ga->xpm[3].box_rel, RED);
		mx_fill_img_bg(&ga->xpm[3], &ga->xpm[1]);
		mx_draw_img(&ga->xpm[3]);
	}

	return (0);
	(void)ga;
}

int	hook_mouse_move(int x, int y, t_game *ga)
{
	fprintf(stderr, "<> mouse move  [%i],[%i]\n", x, y);
	ga->mouse = mx_pt(x, y);

	if (mx_mouse_aabb(ga->mouse, ga->xpm[3].box_abs))
	{
		mx_draw_aabb(&ga->xpm[3], ga->xpm[3].box_rel, CYAN);
		mx_draw_img(&ga->xpm[3]);
	
		// mlx_mouse_hide(ga->mlx_ptr, ga->win.ptr);
	}
	else
	{
		// if (mx_mouse_aabb(ga->mouse, ga->win.box))
			// mlx_mouse_show(ga->mlx_ptr, ga->win.ptr);
	}

#if 0
	int	k = -1;
	for (int i = 0; i < 8; i++)
	{
		if (mx_mouse_aabb(ga->mouse, ga->piece[i].img.box_abs))
			k = i;
		else
			ga->piece[i].mouseover = false;
	}
	if (k != -1)
			ga->piece[k].mouseover = true;
#endif
	return (0);
}

int	hook_frame(t_game *ga)
{
	sleep(0.1);
	// fprintf(stderr, "<> mouse [%i],[%i]\n", ga->mouse.x, ga->mouse.y);

#if 0
	for (int i = 0; i < 8; i++)
	{
		if (ga->piece[i].mouseover == true)
			mx_draw_aabb(&ga->piece[i].img, ga->piece[i].img.box_rel, WHITE);
	}
#endif
	return (0);
	(void)ga;
}

#if 1
void	main_loop(t_game *ga)
{
	mlx_loop_hook(ga->mlx_ptr, &hook_frame, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_KEYDOWN, 1L << 0, &hook_key_press, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_KEYUP, 1L << 1, &hook_key_release, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_MOUSEDOWM, 1L << 2, &hook_mouse_down, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_MOUSEUP, 1L << 3, &hook_mouse_up, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_MOUSEMOVE, 1L << 6, &hook_mouse_move, ga);
	mlx_hook(ga->win.ptr, MX_EVENT_CROSSDESTROY,	0, &hook_crossdestroy, ga);
	mlx_loop(ga->mlx_ptr);
	return ;
}
#endif
