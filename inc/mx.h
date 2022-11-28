/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:08:31 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/11 23:36:59by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MX_H
# define MX_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "mx_color.h"
# include "mx_event.h"
# include <stdbool.h>
# include <assert.h>
# include <math.h>
# include <sys/time.h>

# define LOG		c_magenta();\
					printf("%s:%d %s()\n", __FILE__,__LINE__, __FUNCTION__);\
					c_reset();

# define MX_VERBOSE	0

typedef unsigned int	t_uint;

typedef struct s_2Dpt
{
	int	x;
	int	y;
}	t_2Dpt;

typedef struct s_2Dvec
{
	int	x;
	int	y;
}	t_2Dvec;

typedef struct s_line
{
	t_2Dpt	a;
	t_2Dpt	b;
}	t_line;

typedef struct s_ccl
{
	t_2Dpt	center;
	int		radius;
}	t_ccl;

typedef struct s_tri
{
	t_2Dpt	a;
	t_2Dpt	b;
	t_2Dpt	c;
}	t_tri;

typedef struct s_aabb
{
	t_2Dpt	origin;
	t_2Dvec	lenght;
}	t_aabb;

typedef struct s_win
{
	void	*ptr;
	int		height;
	int		width;
	int		x;
	int		y;
	char	*name;
	t_aabb	box;
	void	*mlx_ptr;
}	t_win;

typedef struct s_img
{
	void	*ptr;
	int		height;
	int		width;
	char	*name;
	void	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	t_2Dpt	origin;
	t_aabb	box_abs;
	t_aabb	box_rel;
	void	*mlx_ptr;
	t_win	*win;
}	t_img;

typedef struct s_but
{
	char	*name;
	t_2Dpt	origin;
	t_aabb	box_abs;
	t_aabb	box_rel;

	t_img	img_away;
	t_img	img_over;
	t_img	img_active;

	int		xev_is_in;
	int		xev_action_in;
	int		xev_action_out;

	int		xev_is_press[6];
	int		xev_action_press[6];
	int		xev_action_release[6];
}	t_but;

/* MLX_PTR */
void	*mx_init_mlx(void);
void	mx_destroy_mlx(void *mlx_ptr);

/* WINDOW */
t_win	mx_init_win(void *mlx_ptr, int width, int height, int x, int y);
int		mx_create_win(t_win *win, char *name);
void	mx_destroy_win(t_win *win);

/* IMAGE */
t_img	mx_init_img(void *mlx_ptr, t_win *win, t_2Dpt origin, t_2Dvec size);
int		mx_create_img(t_img *img, char *name);
int		mx_create_xpm_img(t_img *img, char *file);
void	mx_destroy_img(t_img *img);
void	mx_move_abs_xy_img(t_img *img, int x, int y);
void	mx_move_abs_pt_img(t_img *img, t_2Dpt new_origin);
void	mx_move_rel_xy_img(t_img *img, int x, int y);
void	mx_draw_img(t_img *img);
void	mx_fill_img(t_img *img, t_uint hexcolor);
void	mx_fill_img_bg(t_img *front, t_img *backg);
int		mx_reset_img(t_img *img);
void	mx_draw_box_img(t_img *img, t_uint hexcolor);
void	mx_grid_img(t_img *img, t_2Dvec nb_tiles, t_uint hexcolor);
void	mx_putstr_img(t_img *img, t_2Dpt origin, char *str, t_uint hexcolor);
void	mx_putstr_cen_img(t_img *img, char *str, t_uint hexcolor);
void	mx_putnbr_img(t_img *img, t_2Dpt origin, int nbr, t_uint hexcolor);
void	mx_putnbr_cen_img(t_img *img, int nbr, t_uint hexcolor);

/* PIXEL */
bool	mx_sc_pixel_outside_img(t_img *img, int x, int y);
void	mx_draw_pixel(t_img *img, int x, int y, t_uint hexcolor);
t_uint	mx_get_pixel_color(t_img *img, int x, int y);

/* 	LOG */
void	mx_log_msg(const char *msg);
void	mx_log_ptr(const char *msg, void *ptr);
void	mx_log_pt(const char *msg, t_2Dpt pt);
void	mx_log_vec(const char *msg, t_2Dvec vec);
void	mx_log_line(const char *msg, t_line ln);
void	mx_log_circle(const char *msg, t_ccl cl);
void	mx_log_aabb(const char *msg, t_aabb box);
void	mx_log_img(const char *msg, t_img *img);
void	mx_log_win(const char *msg, t_win *win);

/* POINT */
t_2Dpt	mx_pt(int x, int y);
void	mx_log_pt(const char *msg, t_2Dpt pt);
void	mx_draw_pt(t_img *img, t_2Dpt pt, t_uint hexcolor);
bool	mx_same_pt(t_2Dpt pt_a, t_2Dpt pt_b);

/* VECTOR */
t_2Dvec	mx_vec(int x, int y);
void	mx_log_vec(const char *msg, t_2Dvec vec);
t_2Dpt	mx_pt_add_vec(t_2Dpt pt, t_2Dvec vec);
t_2Dpt	mx_pt_sub_vec(t_2Dpt pt, t_2Dvec vec);
t_2Dvec	mx_vec_add_vec(t_2Dvec vec_a, t_2Dvec vec_b);
t_2Dvec	mx_vec_sub_vec(t_2Dvec vec_a, t_2Dvec vec_b);
t_2Dvec	mx_mul_vec(t_2Dvec vec, int scalar);
t_2Dvec	mx_div_vec(t_2Dvec vec, int scalar);
bool	mx_same_vec(t_2Dvec vec_a, t_2Dvec vec_b);

/* LINE */
t_line	mx_line_wh(int x, int y, int w, int h);
t_line	mx_line_xy(int x1, int y1, int x2, int y2);
t_line	mx_line(t_2Dpt pt_a, t_2Dpt pt_b);
void	mx_log_line(const char *msg, t_line ln);
void	mx_draw_line(t_img *img, t_line ln, t_uint hexcolor);
bool	mx_same_line(t_line ln_k, t_line ln_q);

/* CIRCLE */
t_ccl	mx_circle(t_2Dpt center, int radius);
void	mx_log_circle(const char *msg, t_ccl cl);
void	mx_draw_circle(t_img *img, t_2Dpt center, int radius, t_uint hexcolor);
void	mx_draw_cl(t_img *img, t_ccl cl, t_uint hexcolor);
void	mx_draw_circle_topleft(t_img *img, t_2Dpt pt, int radius, t_uint hexcolor);
void	mx_fill_circle(t_img *img, t_2Dpt center, int radius, t_uint hexcolor);
void	mx_fill_circle_topleft(t_img *img, t_2Dpt pt, int radius, t_uint hexcolor);
bool	mx_coll_xy_ccl(int x, int y, t_ccl cl);
bool	mx_coll_pt_ccl(t_2Dpt pt, t_ccl cl);
bool	mx_coll_ccl(t_ccl cc1, t_ccl cc2);
bool	mx_ccl_in_ccl(t_ccl cc1, t_ccl cc2);
void	mx_grid_circle(t_img *img, t_ccl cl, t_2Dvec nb_tiles, t_uint hexcolor);
void	mx_draw_line_in_ccl(t_img *img, t_line ln, t_ccl cl, t_uint hexcolor);

/* TRIANGLE */
t_tri	mx_triangle(t_2Dpt a, t_2Dpt b, t_2Dpt c);
void	mx_log_triangle(const char *msg, t_tri tr);
void	mx_draw_triangle(t_img *img, t_tri tr, t_uint hexcolor);
bool	mx_coll_pt_triangle(t_2Dpt pt, t_tri tr);
bool	mx_coll_xy_triangle(int x, int y, t_tri tr);

/* AABB AXIS ALIGNED BOUNDING BOX */
t_aabb	mx_aabb(t_2Dpt origin, t_2Dvec lenght);
void	mx_log_aabb(const char *msg, t_aabb box);
void	mx_draw_aabb(t_img *img, t_aabb box, t_uint hexcolor);
void	mx_fill_aabb(t_img *img, t_aabb box, t_uint hexcolor);
void	mx_fill_2aabb(t_img *img, t_aabb box1, t_aabb box2, t_uint hexcolor);
void	mx_fill_not2aabb(t_img *img, t_aabb box1, t_aabb box2, t_uint hexcolor);
void	mx_grid_aabb(t_img *img, t_aabb box, t_2Dvec nb_tiles, t_uint hexcolor);
bool	mx_coll_xy_aabb(int x, int y, t_aabb box);
bool	mx_coll_pt_aabb(t_2Dpt pt, t_aabb box);
bool	mx_coll_pt_2aabb(t_2Dpt pt, t_aabb box1, t_aabb box2);
bool	mx_coll_aabb(t_aabb box1, t_aabb box2);
bool	mx_aabb_in_aabb(t_aabb box_inside, t_aabb box_around);
bool	mx_ccl_in_aabb(t_ccl cl, t_aabb box_around);
void	mx_draw_pn_border_aabb(t_img *img, t_aabb box, int border_size, t_uint hexcolor);
void	mx_draw_lt_border_aabb(t_img *img, t_aabb box, int border_size, t_uint hexcolor);

typedef struct s_mouse_button
{
	int		event;
	t_2Dpt	pos;
}	t_mouse_button;

typedef struct s_event_stat
{
	int				mlx_keycode;
	int				key[600];

	t_2Dpt			mouse_pos;
	int				mouse_event;
	t_mouse_button	mouse[6];
	int				win_cross;
}	t_evstat;
/* HOOK */
void	mx_hook_init(void *win_ptr, t_evstat *ev);
int		mx_hook_key_press(int keycode, t_evstat *ev);
int		mx_hook_key_release(int keycode, t_evstat *ev);
int		mx_hook_mouse_down(int button, int x, int y, t_evstat *ev);
int		mx_hook_mouse_up(int button, int x, int y, t_evstat *ev);
int		mx_hook_mouse_move(int x, int y, t_evstat *ev);
int		mx_hook_win_cross(t_evstat *ev);

/* EVSTAT */
int		mx_is_ppkey(int keycode);
void	mx_set_ppkey(t_evstat *ev, int event, int keycode);
int		mx_get_ppkey(t_evstat *ev, int keycode);
char	*mx_get_ppkey_name(int keycode);
void	mx_log_key_evstat(int event, int keycode);
void	mx_add_key_evstat(t_evstat *ev, int event, int keycode);
void	mx_log_mouse_evstat(int event, int button, t_2Dpt pos);
void	mx_add_mouse_evstat(t_evstat *ev, int event, int button, t_2Dpt pos);
void	mx_add_win_cross_evstat(t_evstat *ev);

typedef long long	t_time;

typedef struct s_loop
{
	int				active;
	int				loop_id;
	int				last_loop_id;
	t_time			time_origin;
	t_time			time_elapsed;
	t_time			timeout;
	t_time			last_frame_duration;
	int				fps;
	float			real_fps;
	int				usleep_duration;
}	t_loop;

void	mx_wait_fps(int frame_per_second);
t_time	mx_sc_time_ms(void);
t_time	mx_time_ms(void);
int		mx_time_loop(t_loop *loop, int fps, int sec_timeout);

/* BUTTON */
t_but	mx_init_button(void *mlx_ptr, t_win *win, t_2Dpt origin, t_2Dvec size);
int		mx_create_button(t_but *bt, char *name);
void	mx_destroy_button(t_but *bt);
void	mx_handle_button(t_but *bt, t_evstat *ev);
// void	mx_draw_button(t_but *bt, t_evstat *ev);
void	mx_log_button(const char *msg, t_but *bt);

// DEPRECATED BELOW // TODO

/* OBB ORIENTED BOUNDING BOX */
//todo

typedef struct	s_test
{
	void	*mlx_ptr;
	t_win	win;
	t_img	img;
	t_img	img2;
	t_img	img3;

}	t_test;

/*	EVENTS	*/
// void	main_loop(t_test *m);

bool	mx_mouse_aabb(t_2Dpt mouse, t_aabb box);

#endif /* MX_H */
