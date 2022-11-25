/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:12:43 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/25 14:34:59 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	log_com(t_game *ga)
{
	dprintf(2, "==========================================\n");
	LOG
	if (ga->server && ga->client)
		dprintf(2, "\033[1;31mFATAL ERROR SERV/CL\n");
	if (ga->server == true)
		dprintf(2, "\033[1;32mSERVER\n");
	if (ga->client == true)
		dprintf(2, "\033[1;32mCLIENT\n");
	dprintf(2, "\033[0;35m");
	dprintf(2, "PLAYER   : [%s] [%s]\n", ga->profil_you.name, ga->profil_you.file);
	dprintf(2, "OPPONENT : [%s] [%s]\n", ga->profil_opp.name, ga->profil_opp.file);
	dprintf(2, "\033[0m\n");
	dprintf(2, "==========================================\n");
}

int	server_exist(void)
{
	char	**namelist;

	dir_log(PATH_COMDIR);
	if (dir_size(PATH_COMDIR) > 1)
	{
		LOG
		dprintf(2, "ERROR com dir broken:too many files\n");
		abort();
	}
	namelist = dir_namelist(PATH_COMDIR);
	if (!namelist)
		return (0);
	ft_arfree(namelist);
	return (1);
}

static void	parse_opponent_name(t_game *ga)
{
	int	i;

	assert(ga->profil_opp.file);
	i = 0;
	while (ga->profil_opp.file[i])
	{
		if (ga->profil_opp.file[i] == '_')
			break ;
		i++;
	}
	ga->profil_opp.name = ft_strldup(ga->profil_opp.file, i + 1);
	dprintf(2, "JOIN GAME WITH OPPONENT: [%s]\n", ga->profil_opp.name);
}

void	create_server(t_game *ga)
{
	char	**namelist;

	dprintf(2, "CREATE GAME AS SERVER / WAITING FOR CLIENT OPPONENT\n");
	ga->server = 1;
	ga->client = 0;
	ga->profil_you.file = get_username_code();
	create_comfile(ga->profil_you.file);

	ga->profil_you.name = get_username();
	waiting_room(ga);
	if (dir_size(PATH_COMDIR) != 2)
	{
		LOG
		dprintf(2, "ERROR com dir broken: invalid files (2)\n");
		abort();
	}
	namelist = dir_namelist(PATH_COMDIR);
	assert(namelist);
	if (ft_strcmp(ga->profil_you.file, namelist[0]))
		ga->profil_opp.file = ft_strdup(namelist[0]);
	else
		ga->profil_opp.file = ft_strdup(namelist[1]);
	ft_arfree(namelist);

	parse_opponent_name(ga);
	starting_room(ga);
	assert(ga->server == true);
}

void	create_client(t_game *ga)
{
	char	**namelist;

	dprintf(2, "CREATE GAME AS CLIENT / JOIN SERVER OPPONENT\n");
	namelist = dir_namelist(PATH_COMDIR);
	if (!namelist)
		abort();
	ga->server = 0;
	ga->client = 1;

#ifdef GAME_OPPONENT_NAME

	ga->profil_you.file = set_username_code(GAME_OPPONENT_NAME);
	ga->profil_you.name = ft_strdup(GAME_OPPONENT_NAME);

#else

	ga->profil_you.file = get_username_code();
	ga->profil_you.name = get_username();

#endif

	create_comfile(ga->profil_you.file);

	ga->profil_opp.file = ft_strdup(namelist[0]);
	ft_arfree(namelist);

	parse_opponent_name(ga);
	starting_room(ga);
	assert(ga->client == true);
}
