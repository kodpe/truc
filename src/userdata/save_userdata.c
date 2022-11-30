/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_userdata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:59:37 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 23:33:24 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	save_userdata(t_userdata *ud, char *name)
{
	char	*path;
	int		fd;

	LOG
	assert(name);
	path = ft_strjointri(PATH_USERDATA, name, ".ud");
	if (!path)
		abort();
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		abort();
	free(path);
	dprintf(fd, " %s %s", ud->name, ud->personal_user_photo);
	dprintf(fd, " %il %ix", ud->lvl, ud->xp);
	dprintf(fd, " %iw %il %ir", ud->nb_win, ud->nb_loose, ud->winrate);
	for (int i = 0; i < 4; i++)
		dprintf(fd, " %ic", ud->pieces_catch[i]);
	for (int i = 0; i < 4; i++)
		dprintf(fd, " %il", ud->pieces_loose[i]);
	for (int i = 0; i < 4; i++)
		dprintf(fd, " %im", ud->pieces_moves[i]);
	for (int i = 0; i < 4; i++)
		dprintf(fd, " %iu", ud->sp_tiles_use[i]);
	for (int i = 0; i < 8; i++)
		dprintf(fd, " %iw", ud->witch_formes[i]);
	dprintf(fd, " %it", ud->total_game_time);
	dprintf(fd, " %ia", ud->average_game_time);
	for (int i = 0; i < 5; i++)
		dprintf(fd, " %id", ud->date[i]);
	dprintf(fd, "\n");
	close(fd);
}

/* procedure

1. GET UD
2. play a game .. and add pieces_catch, sp_tiles_use, etc...
3. UPDATE UD with 1/0 and game_time_sec
4. SAVE UD
5. go to profil ..
6. GET UD with all updates , last date, etc...
*/
