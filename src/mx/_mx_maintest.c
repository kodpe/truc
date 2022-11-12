/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _mx_maintest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 23:03:15 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/12 07:05:43 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

#define MX_TEST

#ifdef MX_TEST


// # define MX_TEST_1
// # define MX_TEST_2
// # define MX_TEST_3
// # define MX_TEST_4
// # define MX_TEST_5
// # define MX_TEST_6
// # define MX_TEST_7
# define MX_TEST_8


int	main(void)
{
	t_test	all;

# ifdef MX_TEST_1
/* mx_init_mlx() + mx_destroy_mlx() OK */
	all.mlx_ptr = mx_init_mlx();
	getchar();
	mx_destroy_mlx(all.mlx_ptr);
# endif


# ifdef MX_TEST_2
/* mx_create_win() + mx_destroy_win() OK */
	all.mlx_ptr = mx_init_mlx();
	all.win = mx_init_win(all.mlx_ptr, 500, 500);
	if (mx_create_win(&all.win, "mx test"))
		abort();
	getchar();
	mx_destroy_win(&all.win);
	mx_destroy_mlx(all.mlx_ptr);
# endif

# ifdef MX_TEST_3
/* mx_create_img() + mx_destroy_img() OK */
	all.mlx_ptr = mx_init_mlx();
	all.win = mx_init_win(all.mlx_ptr, 500, 500);
	if (mx_create_win(&all.win, "mx test"))
		abort();
	all.img = mx_init_img(all.mlx_ptr, &all.win, mx_pt(0, 0), mx_vec(100, 100));
	if (mx_create_img(&all.img, "mx image"))
		abort();
	// mx_move_xy_img(&all.img, 10, 10); //!
	mx_fill_img(&all.img, BURLY_WOOD);
	mx_draw_img(&all.img);
	getchar();
	mx_destroy_img(&all.img);
	mx_destroy_win(&all.win);
	mx_destroy_mlx(all.mlx_ptr);
# endif

# ifdef MX_TEST_4
/* TEST 4: mx_draw_line() OK */
	all.mlx_ptr = mx_init_mlx();
	all.win = mx_init_win(all.mlx_ptr, 500, 500);
	if (mx_create_win(&all.win, "mx test"))
		abort();
	all.img = mx_init_img(all.mlx_ptr, &all.win, mx_pt(0, 0), mx_vec(400, 400));
	if (mx_create_img(&all.img, "mx image"))
		abort();
	mx_fill_img(&all.img, DARK_BLUE);
	mx_move_xy_img(&all.img, 50, 50);
	mx_draw_line(&all.img, mx_line(mx_pt(100, 100), mx_pt(300, 200)), WHITE);
	mx_draw_line(&all.img, mx_line(mx_pt(300, 100), mx_pt(100, 300)), WHITE);
	mx_draw_line(&all.img, mx_line(mx_pt(100, 200), mx_pt(200, 100)), WHITE);
	mx_draw_line(&all.img, mx_line(mx_pt(300, 300), mx_pt(200, 300)), WHITE);
	mx_draw_line(&all.img, mx_line(mx_pt(0, 0), mx_pt(400, 400)), WHITE);
	mx_draw_line(&all.img, mx_line(mx_pt(400, 400), mx_pt(0, 0)), WHITE);
	mx_draw_line(&all.img, mx_line(mx_pt(0, 400), mx_pt(400, 0)), WHITE);
	mx_draw_line(&all.img, mx_line(mx_pt(400, 0), mx_pt(0, 400)), WHITE);

	mx_draw_line(&all.img, mx_line(mx_pt(-1, 0), mx_pt(400, 400)), WHITE);
	mx_draw_line(&all.img, mx_line(mx_pt(0, -1), mx_pt(400, 400)), WHITE);
	mx_draw_line(&all.img, mx_line(mx_pt(0, 0), mx_pt(401, 400)), WHITE);
	mx_draw_line(&all.img, mx_line(mx_pt(0, 0), mx_pt(400, 401)), WHITE);

	mx_draw_img(&all.img);
	getchar();
	mx_destroy_img(&all.img);
	mx_destroy_win(&all.win);
	mx_destroy_mlx(all.mlx_ptr);
# endif

# ifdef MX_TEST_5
/* mx_draw_aabb() OK */
	all.mlx_ptr = mx_init_mlx();
	all.win = mx_init_win(all.mlx_ptr, 500, 500);
	if (mx_create_win(&all.win, "mx test"))
		abort();
	all.img = mx_init_img(all.mlx_ptr, &all.win, mx_pt(0, 0), mx_vec(400, 400));
	if (mx_create_img(&all.img, "mx image"))
		abort();
	mx_fill_img(&all.img, DARK_GRAY);
	mx_draw_aabb(&all.img, mx_aabb(mx_pt(0, 0), mx_vec(100, 100)), LIME);
	mx_draw_aabb(&all.img, mx_aabb(mx_pt(50, 100), mx_vec(100, 50)), RED);
	mx_draw_aabb(&all.img, mx_aabb(mx_pt(200, 0), mx_vec(150, 200)), BLUE);
	mx_draw_aabb(&all.img, mx_aabb(mx_pt(200, -1), mx_vec(150, 200)), HOT_PINK);
	mx_draw_aabb(&all.img, mx_aabb(mx_pt(-200, 0), mx_vec(150, 200)), HOT_PINK);
	mx_draw_aabb(&all.img, mx_aabb(mx_pt(200, 0), mx_vec(150, 2000)), HOT_PINK);
	mx_draw_aabb(&all.img, mx_aabb(mx_pt(0, 0), mx_vec(1500, 200)), HOT_PINK);
	mx_draw_img(&all.img);
	getchar();
	mx_destroy_img(&all.img);
	mx_destroy_win(&all.win);
	mx_destroy_mlx(all.mlx_ptr);
# endif

# ifdef MX_TEST_6
/* mx_fill_img() + mx_move_img() OK */
	all.mlx_ptr = mx_init_mlx();
	all.win = mx_init_win(all.mlx_ptr, 500, 500);
	if (mx_create_win(&all.win, "mx test"))
		abort();
	all.img = mx_init_img(all.mlx_ptr, &all.win, mx_pt(0, 0), mx_vec(400, 400));
	if (mx_create_img(&all.img, "mx image"))
		abort();
	mx_move_xy_img(&all.img, 100, 100);
	mx_fill_img(&all.img, DARK_GRAY);
	mx_move_xy_img(&all.img, 100, 99);
	mx_fill_img(&all.img, ORCHID);
	// mx_move_xy_img(&all.img, 200, 200);

	mx_draw_aabb(&all.img, mx_aabb(mx_pt(0, 0), mx_vec(100, 100)), LIME);
	mx_fill_aabb(&all.img, mx_aabb(mx_pt(50, 100), mx_vec(100, 50)), RED);
	mx_fill_aabb(&all.img, mx_aabb(mx_pt(200, 0), mx_vec(150, 200)), BLUE);
	mx_draw_img(&all.img);
	getchar();
	mx_destroy_img(&all.img);
	mx_destroy_win(&all.win);
	mx_destroy_mlx(all.mlx_ptr);
# endif

# ifdef MX_TEST_7
/* mx_circle() OK */
	all.mlx_ptr = mx_init_mlx();
	all.win = mx_init_win(all.mlx_ptr, 500, 500);
	if (mx_create_win(&all.win, "mx test"))
		abort();
	all.img = mx_init_img(all.mlx_ptr, &all.win, mx_pt(0, 0), mx_vec(400, 400));
	if (mx_create_img(&all.img, "mx image"))
		abort();
	mx_move_xy_img(&all.img, 100, 100);
	mx_fill_img(&all.img, DARK_GRAY);
	mx_move_xy_img(&all.img, 100, 99);
	mx_fill_img(&all.img, BLACK);
	// mx_move_xy_img(&all.img, 200, 200);

	mx_draw_aabb(&all.img, mx_aabb(mx_pt(0, 0), mx_vec(100, 100)), LIME);
	mx_fill_aabb(&all.img, mx_aabb(mx_pt(50, 100), mx_vec(100, 50)), RED);
	mx_draw_cl(&all.img, mx_circle(mx_pt(200, 200), 40), YELLOW);
	mx_draw_cl(&all.img, mx_circle(mx_pt(200, 200), 50), ORANGE);
	mx_draw_cl(&all.img, mx_circle(mx_pt(250, 200), 1), ORANGE);
	mx_draw_circle_topleft(&all.img, mx_pt(200, 200), 30, RED);
	mx_draw_circle_topleft(&all.img, mx_pt(0, 0), 200, LIME);
	mx_draw_circle_topleft(&all.img, mx_pt(0, 100), 70, RED);
	mx_fill_circle_topleft(&all.img, mx_pt(0, 100), 70, BLUE_VIOLET);
	mx_draw_img(&all.img);
	getchar();
	mx_destroy_img(&all.img);
	mx_destroy_win(&all.win);
	mx_destroy_mlx(all.mlx_ptr);
# endif

# ifdef MX_TEST_8
/* EVENTS XOXKX */
	all.mlx_ptr = mx_init_mlx();
	all.win = mx_init_win(all.mlx_ptr, 500, 500);
	if (mx_create_win(&all.win, "mx test"))
		abort();
	all.img = mx_init_img(all.mlx_ptr, &all.win, mx_pt(0, 0), mx_vec(400, 400));
	if (mx_create_img(&all.img, "mx image"))
		abort();
	mx_move_xy_img(&all.img, 100, 100);
	mx_fill_img(&all.img, DARK_GRAY);
	mx_move_xy_img(&all.img, 100, 99);
	mx_fill_img(&all.img, BLACK);
	// mx_move_xy_img(&all.img, 200, 200);

	mx_draw_aabb(&all.img, mx_aabb(mx_pt(0, 0), mx_vec(100, 100)), LIME);
	mx_fill_aabb(&all.img, mx_aabb(mx_pt(50, 100), mx_vec(100, 50)), RED);
	mx_draw_cl(&all.img, mx_circle(mx_pt(200, 200), 40), YELLOW);
	mx_draw_cl(&all.img, mx_circle(mx_pt(200, 200), 50), ORANGE);
	mx_draw_cl(&all.img, mx_circle(mx_pt(250, 200), 1), ORANGE);
	mx_draw_circle_topleft(&all.img, mx_pt(200, 200), 30, RED);
	mx_draw_circle_topleft(&all.img, mx_pt(0, 0), 200, LIME);
	mx_draw_circle_topleft(&all.img, mx_pt(0, 100), 70, RED);
	mx_fill_circle_topleft(&all.img, mx_pt(0, 100), 70, BLUE_VIOLET);
	mx_draw_img(&all.img);

	main_loop(&all);
	mx_destroy_img(&all.img);
	mx_destroy_win(&all.win);
	mx_destroy_mlx(all.mlx_ptr);

# endif

	return (0);
	(void)all;
}

# endif

void	ft_void(void)
{
	return ;
}
