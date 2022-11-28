/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:08:29 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/28 22:48:07 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	_sc_check_multiplayer(t_game *ga)
{
	ga->lp_game.active = 0;
	LOG
	log_com(ga);
	assert(ga->profil_you.name);
	assert(ga->profil_you.file);
	assert(ga->profil_you.path);
	assert_comfile(ga->profil_you.path);
	assert(ga->server != ga->client);
	if (ga->server)
		assert(ga->profil_opp.name == NULL && ga->profil_opp.file == NULL);
	if (ga->client)
		assert(ga->profil_opp.name && ga->profil_opp.file);
}

static void	_init_mlx(t_game *ga)
{
	ga->mlx_ptr = mx_init_mlx();
	if (!ga->mlx_ptr)
		abort();
	if (ga->server)
	{
		ga->win = mx_init_win(ga->mlx_ptr, 1200, 900, 1300, 0);
		if (mx_create_win(&ga->win, "server"))
			abort();
	}
	if (ga->client)
	{
		ga->win = mx_init_win(ga->mlx_ptr, 1200, 900, 0, 0);
		if (mx_create_win(&ga->win, "client"))
			abort();
	}
}

static int	_loop_manager(t_game *ga)
{
	if (ga->lp_menu.active)
		loop_menu(ga);

	if (ga->lp_waitopp.active)
		loop_waitopp(ga);
	if (ga->lp_startgame.active)
		loop_startgame(ga);
	if (ga->lp_game.active)
		loop_game(ga);
	if (ga->lp_wantquit.active)
		loop_wantquit(ga);
	return (0);
}

void	_global_mlx_loop(t_game *ga)
{
	if (ga->server)
		goto_loop(ga, LOOP_ID_MENU, LOOP_ID_WAITOPP);
	if (ga->client)
		goto_loop(ga, LOOP_ID_MENU, LOOP_ID_STARTGAME);

	goto_loop(ga, 0, LOOP_ID_MENU);

	mlx_loop_hook(ga->mlx_ptr, &_loop_manager, ga);
	mx_hook_init(ga->win.ptr, &ga->evstat);
	mlx_loop(ga->mlx_ptr);
}

int	main(void)
{
	t_game	ga;
	time_t	t;

	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	srand(time(&t));
	ft_memset(&ga, 0, sizeof(t_game));
	
	if (server_exist())
		create_client(&ga);
	else
		create_server(&ga);
	_sc_check_multiplayer(&ga);

	_init_mlx(&ga);
	_global_mlx_loop(&ga);
	mx_destroy_win(&ga.win);
	mx_destroy_mlx(ga.mlx_ptr);
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
