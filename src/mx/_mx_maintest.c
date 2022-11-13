/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _mx_maintest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 23:03:15 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/13 11:49:33by sloquet          ###   ########.fr       */
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
// # define MX_TEST_8
// # define MX_TEST_9
// # define MX_TEST_10
// # define MX_TEST_11
# define MX_TEST_12


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
	mx_fill_circle_topleft(&all.img, mx_pt(100, 100), 70, 0xEF00FF00);
	mx_fill_circle_topleft(&all.img, mx_pt(200, 100), 70, 0xAA00FF00);
	mx_draw_img(&all.img);

	main_loop(&all);
	mx_destroy_img(&all.img);
	mx_destroy_win(&all.win);
	mx_destroy_mlx(all.mlx_ptr);

# endif

# ifdef MX_TEST_9
/* TRIANGLE */
	all.mlx_ptr = mx_init_mlx();
	all.win = mx_init_win(all.mlx_ptr, 500, 500);
	if (mx_create_win(&all.win, "mx test"))
		abort();
	all.img = mx_init_img(all.mlx_ptr, &all.win, mx_pt(0, 0), mx_vec(500, 500));
	if (mx_create_img(&all.img, "mx image"))
		abort();
	mx_draw_aabb(&all.img, mx_aabb(mx_pt(10, 10), mx_vec(480, 480)), LIME);

	// mx_draw_cl(&all.img, mx_circle(mx_pt(200, 200), 40), YELLOW);
	// mx_draw_cl(&all.img, mx_circle(mx_pt(200, 200), 50), ORANGE);

	t_tri tr = mx_triangle(mx_pt(90, 80), mx_pt(70, 220), mx_pt(340, 200));
	t_2Dpt	pt = mx_pt(40, 100);
	t_2Dpt	pt2 = mx_pt(376, 185);

	mx_draw_triangle(&all.img, tr, YELLOW);
	mx_log_triangle("ici le tri", tr);
	mx_draw_pt(&all.img, pt, RED);
	mx_draw_pt(&all.img, pt2, RED);
	if (mx_coll_pt_triangle(pt, tr))
		printf("\033[0;32mONE COLLISION\033[0m\n");
	else
		printf("\033[0;31mZERO COLLISION\033[0m\n");
	if (mx_coll_pt_triangle(pt2, tr))
		printf("\033[0;32mONE COLLISION\033[0m\n");
	else
		printf("\033[0;31mZERO COLLISION\033[0m\n");

	mx_draw_circle_topleft(&all.img, mx_pt(200, 200), 30, GRAY);

	mx_draw_aabb(&all.img, mx_aabb(mx_pt(40, 40), mx_vec(320, 320)), BLUE);

	mx_draw_img(&all.img);

	main_loop(&all);
	mx_destroy_img(&all.img);
	mx_destroy_win(&all.win);
	mx_destroy_mlx(all.mlx_ptr);

# endif

# ifdef MX_TEST_10
/* AABB GRID */
	all.mlx_ptr = mx_init_mlx();
	all.win = mx_init_win(all.mlx_ptr, 500, 500);
	if (mx_create_win(&all.win, "mx test"))
		abort();
	all.img = mx_init_img(all.mlx_ptr, &all.win, mx_pt(0, 0), mx_vec(500, 500));
	if (mx_create_img(&all.img, "mx image"))
		abort();
	mx_draw_aabb(&all.img, mx_aabb(mx_pt(10, 10), mx_vec(480, 480)), LIME);

	mx_draw_aabb(&all.img, mx_aabb(mx_pt(40, 40), mx_vec(320, 320)), BLUE);

	mx_grid_aabb(&all.img, mx_aabb(mx_pt(50, 50), mx_vec(300, 300)), \
		mx_vec(200, 200), LIME);
	mx_grid_aabb(&all.img, mx_aabb(mx_pt(51, 51), mx_vec(300, 300)), \
		mx_vec(200, 200), BLUE);

	mx_grid_aabb(&all.img, mx_aabb(mx_pt(50, 360), mx_vec(400, 120)), \
		mx_vec(7, 15), LIME);
	mx_grid_aabb(&all.img, mx_aabb(mx_pt(50, 360), mx_vec(400, 120)), \
		mx_vec(11, 9), BLUE);

	mx_draw_img(&all.img);

	main_loop(&all);
	mx_destroy_img(&all.img);
	mx_destroy_win(&all.win);
	mx_destroy_mlx(all.mlx_ptr);

# endif

# ifdef MX_TEST_11
/* CIRCLE GRID */
	all.mlx_ptr = mx_init_mlx();
	all.win = mx_init_win(all.mlx_ptr, 1200, 1200);
	if (mx_create_win(&all.win, "mx test"))
		abort();
	all.img = mx_init_img(all.mlx_ptr, &all.win, mx_pt(0, 0), mx_vec(1200, 1200));
	if (mx_create_img(&all.img, "mx image"))
		abort();
	// mx_draw_aabb(&all.img, mx_aabb(mx_pt(10, 10), mx_vec(480, 480)), LIME);

	// mx_draw_aabb(&all.img, mx_aabb(mx_pt(40, 40), mx_vec(320, 320)), BLUE);

	t_ccl	cl = mx_circle(mx_pt(600, 600), 300);
	mx_grid_circle(&all.img, cl, mx_vec(4, 3), GREEN);

	mx_draw_img(&all.img);

	main_loop(&all);
	mx_destroy_img(&all.img);
	mx_destroy_win(&all.win);
	mx_destroy_mlx(all.mlx_ptr);

# endif

# ifdef MX_TEST_12
/* XPM IMG */
	all.mlx_ptr = mx_init_mlx();
	all.win = mx_init_win(all.mlx_ptr, 1600, 700);
	if (mx_create_win(&all.win, "mx test"))
		abort();

	all.img = mx_init_img(all.mlx_ptr, &all.win, mx_pt(1, 1), mx_vec(1, 1));
	if (mx_create_xpm_img(&all.img, "assets/128w/128w_yama-uba.xpm"))
		abort();

	all.img2 = mx_init_img(all.mlx_ptr, &all.win, mx_pt(200, 1), mx_vec(1, 1));
	if (mx_create_xpm_img(&all.img2, "assets/128w/f128w_yama-uba.xpm"))
		abort();

	// all.img3 = mx_init_img(all.mlx_ptr, &all.win, mx_pt(400, 1), mx_vec(1, 1));
	// if (mx_create_xpm_img(&all.img3, "assets/128w/ff128w_yama-uba.xpm"))
		// abort();

	all.img3 = mx_init_img(all.mlx_ptr, &all.win, mx_pt(0, 0), mx_vec(1600, 700));
	if (mx_create_img(&all.img3, "mx image"))
		abort();


	// mx_draw_aabb(&all.img3, mx_aabb(mx_pt(0, 200), mx_vec(513, 513)), LIME);
	mx_draw_aabb(&all.img3, mx_aabb(mx_pt(0, 200), mx_vec(250, 250)), LIME);
	mx_draw_aabb(&all.img3, mx_aabb(mx_pt(0, 200), mx_vec(120, 120)), LIME);
	mx_draw_aabb(&all.img3, mx_aabb(mx_pt(0, 200), mx_vec(100, 100)), LIME);
	mx_draw_aabb(&all.img3, mx_aabb(mx_pt(0, 200), mx_vec(64, 64)), LIME);

	mx_grid_aabb(&all.img3, mx_aabb(mx_pt(550, 10), mx_vec(500, 500)), mx_vec(5, 5), LIME);

	mx_draw_aabb(&all.img3, mx_aabb(mx_pt(550, 10), mx_vec(500, 500)), LIME);

	// t_ccl	cl = mx_circle(mx_pt(600, 600), 300);
	// mx_grid_circle(&all.img, cl, mx_vec(4, 3), GREEN);

	mx_draw_img(&all.img3);
	mx_draw_img(&all.img);
	mx_draw_img(&all.img2);

	main_loop(&all);
	mx_destroy_img(&all.img);
	mx_destroy_img(&all.img2);
	mx_destroy_img(&all.img3);
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
