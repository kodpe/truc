/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:47:45 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/11 01:34:20 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pong.h"

static int	exit_cross_st(t_m *m)
{
	pong_exit(m);
	return (0);
}

static int	key_press_st(int keycode, t_m *m)
{
	if (keycode == KEY_ESCAPE)
		pong_exit(m);
#if 0
	if (keycode == KEY_A && m->r1.x > m->box.border)
		m->r1.x -= m->r1.x_pad;

	if (keycode == KEY_D \
			&& m->r1.x + m->r1.x_size < m->g_max.x - m->box.border)
		m->r1.x += m->r1.x_pad;

	if (keycode == KEY_LEFT && m->r2.x > m->box.border)
	{
		send(m, "RL");
		m->r2.x -= m->r2.x_pad;
	}

	if (keycode == KEY_RIGHT \
			&& m->r2.x + m->r2.x_size < m->g_max.x - m->box.border)
	{
		send(m, "RR");
		m->r2.x += m->r2.x_pad;
	}
#endif

	return (0);
}

static void	update_box(t_m *m)
{
	t_img	*img;
	t_2Dpnt	origin;
	t_2Dpnt	max;
	t_2Dpnt	len;

	img = &m->mlx.img[0];
	origin.x = m->box.border - 1;
	origin.y = m->box.border - 1;
	max.x = m->g_max.x - m->box.border;
	max.y = m->g_max.y - m->box.border;
	smlx_box_max(img, origin, max, m->box.color);

	if (SMLX_WIN_SIZE_X > SMLX_WIN_SIZE_Y)
	{
		len.x = SMLX_WIN_SIZE_Y;
		len.y = SMLX_WIN_SIZE_Y;
		origin.x = (SMLX_WIN_SIZE_X - SMLX_WIN_SIZE_Y) / 2;
		origin.y = 0;
	}
	else
	{
		len.x = SMLX_WIN_SIZE_X;
		len.y = SMLX_WIN_SIZE_X;
		origin.x = (SMLX_WIN_SIZE_Y - SMLX_WIN_SIZE_X) / 2;
		origin.y = 0;
	}
	smlx_box_len(img, origin, len, m->box2.color);
}

#if 0
static void	display_score(t_m *m)
{
	char	*sco;
	char	*so;
	char	*scp;
	char	*sp;

	sco = ft_itoa(m->r1.score);
	so = ft_strjointri(m->name_opponent, " ", sco);
	scp = ft_itoa(m->r2.score);
	sp = ft_strjointri(scp, " ", m->name_player);

	mlx_string_put(m->mlx.ptr, m->mlx.win.ptr, \
		40, 14, WHITE, so);
	mlx_string_put(m->mlx.ptr, m->mlx.win.ptr, \
		m->g_max.x - 100, m->g_max.y - 5, WHITE, sp);
	free(sco);
	free(so);
	free(scp);
	free(sp);
}
#endif

static int	game_loop(t_m *m)
{
	usleep(500);
	if (smlx_reset_image(&m->mlx, 0))
		pong_exit(m);
	// smlx_screen_filler(m->mlx.img, 0x00222222);	// dark mode
	// smlx_screen_filler(m->mlx.img, 0x00FFFFFF);	// light mode
	// update_box(m);
	// receive(m);

	// update_ball(m);
	// smlx_grid(m->mlx.img, m->gm_origin, m->gm_lenght, smlx_pos(5, 5), LIME);
	// smlx_box_len(m->mlx.img, smlx_pos(m->gm_origin.x, m->gm_origin.y + m->gm_lenght.y), smlx_pos(m->gm_lenght.x, 100), BLUE_VIOLET);

	for (int i = 0; i < 100; i++)
		smlx_circle_center(m->mlx.img, m->gm_origin, i, RED + i * 5);

	smlx_display_image(&m->mlx, 0, 0, 0);
	// display_score(m);
	return (0);
	update_box(m);
}

void	game_room(t_m *m)
{
	assert(m->player);
	assert(m->opponent);
	assert(m->name_player);
	assert(m->name_opponent);
	mlx_loop_hook(m->mlx.ptr, &game_loop, m);
	mlx_hook(m->mlx.win.ptr, 2, 1L << 0, &key_press_st, m);
	mlx_hook(m->mlx.win.ptr, 17, 0, &exit_cross_st, m);
	mlx_loop(m->mlx.ptr);
}
