/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:12:43 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/25 18:28:00 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	server_exist(void)
{
	char	**namelist;

	if (dir_size(PATH_COMDIR) > 1)
	{
		LOG
		dprintf(2, "ERROR com dir broken: corrupted files or a game is already in progress\n");
		exit(1);
	}
	namelist = dir_namelist(PATH_COMDIR);
	if (!namelist)
		return (0);
	ft_arfree(namelist);
	return (1);
}

void	create_server(t_game *ga)
{
	dprintf(2, "CREATE SERVER: WAITING FOR CLIENT OPPONENT\n");
	ga->server = 1;
	ga->client = 0;
#ifdef SERVER_NAME
	ga->profil_you.name = ft_strdup(SERVER_NAME);
	ga->profil_you.file = set_username_code(SERVER_NAME);
#else
	ga->profil_you.name = get_username();
	ga->profil_you.file = get_username_code();
#endif
	create_comfile(ga->profil_you.file);
}

void	receive_opponent(t_game *ga)
{
	if (dir_size(PATH_COMDIR) != 2)
	{
		free(ga->profil_you.file);
		free(ga->profil_you.name);
		LOG
		dprintf(2, "\033[1;31mEXIT PATH_COMDIR != 2\033[0m\n");
		exit(2);
	}
	ga->profil_opp.file = get_opponent_file(ga->profil_you.file);
	ga->profil_opp.name = parse_opponent_name(ga->profil_opp.file);
	dprintf(2, "JOIN WITH OPPONENT: [%s]\n", ga->profil_opp.name);
}

void	create_client(t_game *ga)
{
	dprintf(2, "CREATE CLIENT: JOIN SERVER OPPONENT\n");
	ga->server = 0;
	ga->client = 1;
#ifdef CLIENT_NAME
	ga->profil_you.name = ft_strdup(CLIENT_NAME);
	ga->profil_you.file = set_username_code(CLIENT_NAME);
#else
	ga->profil_you.name = get_username();
	ga->profil_you.file = get_username_code();
#endif
	create_comfile(ga->profil_you.file);
	receive_opponent(ga);
}
