/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:31:36 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/25 19:38:46 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	game_init(t_game *ga)
{
	time_t	t;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	srand(time(&t));
	ft_memset(ga, 0, sizeof(t_game));

#ifdef SOLO
	dprintf(2, "\033[1;31mSOLO MODE\033[0m\n");
	abort(); // TODO
#endif

#ifdef MULTIPLAYER

	if (server_exist())
		create_client(ga);
	else
		create_server(ga);
	lobby_room(ga);
# if 1
	lobby_exit(ga);
	LOG
	dprintf(2, "\033[1;31mEXIT SUCCESS\033[0m\n");
	exit(0);
# else
	mx_destroy_win(&ga->win);
	mx_destroy_mlx(ga->mlx_ptr);
# endif
#endif
	// MLX INIT
	ga->mlx_ptr = mx_init_mlx();
	if (!ga->mlx_ptr)
		abort();
	if (ga->server)
	{
		ga->win = mx_init_win(ga->mlx_ptr, 1200, 900, 0, 0);
		if (mx_create_win(&ga->win, "server"))
			abort();
	}
	if (ga->client)
	{
		ga->win = mx_init_win(ga->mlx_ptr, 1200, 900, 1300, 0);
		if (mx_create_win(&ga->win, "client"))
			abort();
	}

}
