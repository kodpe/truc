/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:08:29 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 09:46:23 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_destroy_mlx(t_game *ga)
{
	mx_destroy_win(&ga->win);
	mx_destroy_mlx(ga->mlx_ptr);
}

static void	_init_mlx(t_game *ga)
{
	ga->mlx_ptr = mx_init_mlx();
	if (!ga->mlx_ptr)
		abort();

	int	align_x = 0;
	if (rand() % 2 == 0)
		align_x = 1300;
	ga->win = mx_init_win(ga->mlx_ptr, 1200, 900, align_x, 0);
	if (mx_create_win(&ga->win, "server"))
		abort();
}

void	_global_mlx_loop(t_game *ga)
{
	goto_loop(ga, LOOP_START, LOOP_ID_MENU);
	mlx_loop_hook(ga->mlx_ptr, &loop_manager, ga);
	mx_hook_init(ga->win.ptr, &ga->evstat);
	mlx_loop(ga->mlx_ptr);
}

int	main(void)
{
	t_game	ga;
	time_t	t;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	srand(time(&t));
	ft_memset(&ga, 0, sizeof(t_game));
	_init_mlx(&ga);
	_global_mlx_loop(&ga);
	_destroy_mlx(&ga);
	return (0);
}

/*

	char *fps = ft_strdup("..........");
	snprintf(fps, ft_strlen(fps), "%.2f FPS", ga->lp_waitopp.real_fps);
	mx_putstr_img(img,
				  mx_pt(img->origin.x + img->width - ft_strlen(fps) * 6 - 10,
						img->origin.y + img->height - 10), fps, SILVER);
	free(fps);

*/
