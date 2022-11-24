/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:12:43 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/24 23:10:20 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	log_com(t_game *ga)
{
	dprintf(2, "GAME %s VS %s\n", ga->profil_you.name, ga->profil_opp.name);
	dprintf(2, "PLAYER_NAME    : [%s]\n", ga->profil_you.name);
	dprintf(2, "PLAYER_FILE    : [%s]\n", ga->profil_you.file);
	dprintf(2, "OPONNENT_NAME  : [%s]\n", ga->profil_opp.name);
	dprintf(2, "OPONNENT_FILE  : [%s]\n", ga->profil_opp.file);
	if (ga->server)
		dprintf(2, "server : %s\nclient : %s\n", \
			ga->profil_you.name, ga->profil_opp.name);
	else
		dprintf(2, "server : %s\nclient : %s\n", \
			ga->profil_opp.name, ga->profil_you.name);
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
		dprintf(2, "ERROR com dir broken: invalid file\n");
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
	log_com(ga);
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
	ga->profil_you.file = get_username_code();
	create_comfile(ga->profil_you.file);

#ifndef GAME_OPPONENT_NAME
	ga->profil_you.name = get_username();
#else
	ga->profil_you.name = ft_strdup(GAME_OPPONENT_NAME);
#endif
	ga->profil_opp.file = ft_strdup(namelist[0]);
	ft_arfree(namelist);

	parse_opponent_name(ga);
	starting_room(ga);
	log_com(ga);
}
