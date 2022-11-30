/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_userdata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:01:40 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 23:32:10 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
	t_userdata *ud and char **sp can be null
*/
void	show_userdata(t_userdata *ud, char **sp)
{
	if (sp)
		dbg_ar((const char **)sp, "dbg array sp");
	if (!ud)
		return ;
	dprintf(2, "0: name     [%s]\n", ud->name);
	dprintf(2, "1: ph       [%s]\n", ud->personal_user_photo);
	dprintf(2, "2: lvl      [%i]\n", ud->lvl);
	dprintf(2, "3: xp       [%i]\n", ud->xp);
	dprintf(2, "4: nb_win   [%i]\n", ud->nb_win);
	dprintf(2, "5: nb_losse [%i]\n", ud->nb_loose);
	dprintf(2, "6: winrate  [%i]\n", ud->winrate);
	for (int i = 0; i < 4; i++)
		dprintf(2, "%i: pieces_catch %i:[%i]\n", 7+i, i, ud->pieces_catch[i]);
	for (int i = 0; i < 4; i++)
		dprintf(2, "%i: pieces_loose %i:[%i]\n", 11+i, i, ud->pieces_loose[i]);
	for (int i = 0; i < 4; i++)
		dprintf(2, "%i: pieces_moves %i:[%i]\n", 15+i, i, ud->pieces_moves[i]);
	for (int i = 0; i < 4; i++)
		dprintf(2, "%i: sp_tiles_use %i:[%i]\n", 19+i, i, ud->sp_tiles_use[i]);
	for (int i = 0; i < 8; i++)
		dprintf(2, "%i: witch_formes %i:[%i]\n", 23+i, i, ud->witch_formes[i]);
	dprintf(2, "31: total_game_time   [%i]\n", ud->total_game_time);
	dprintf(2, "32: average_game_time [%i]\n", ud->average_game_time);
	for (int i = 0; i < 5; i++)
		dprintf(2, "%i: date %i:[%i]\n", 33+i, i, ud->date[i]);
}

/* procedure

1. GET UD
2. play a game .. and add pieces_catch, sp_tiles_use, etc...
3. UPDATE UD with 1/0 and game_time_sec
4. SAVE UD
5. go to profil ..
6. GET UD with all updates , last date, etc...
*/
