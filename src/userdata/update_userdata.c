/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_userdata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:33:40 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/30 00:17:32 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int _calc_average_game_time(t_userdata *ud)
{
	return (ud->total_game_time / (ud->nb_win + ud->nb_loose));
}

static int	_calc_winrate(int win, int loose)
{
	return (win * 100 / (win + loose));
}

static int _calc_xp(t_userdata *ud)
{
	int	xp;

	xp = 0;
	for (int i = 0; i < 4; i++)
	{
		xp += ud->pieces_catch[i];
		xp += ud->pieces_moves[i];
		xp += ud->sp_tiles_use[i];
	}
	return (xp);
}

static int	_calc_lvl(int xp)
{
	int	i;

	i = 0;
	while (xp > 0)
	{
		xp -= ft_power(2, i);
		i++;
	}
	dprintf(2, "LVL [%i]\n", i);
	return (i);
}

// int date[5]; // h:m D/M/Y
static void	_get_current_date(t_userdata *ud)
{
	time_t		epoch;	
	struct tm	*t;

	epoch = time(NULL);
	t = localtime(&epoch);

	ud->date[0] = t->tm_hour;
	ud->date[1] = t->tm_min;
	ud->date[2] = t->tm_mday;
	ud->date[3] = t->tm_mon;
	ud->date[4] = t->tm_year;
	dprintf(2, "DATE tab [%02d:%02d %02d/%02d/%04d]\n", \
		ud->date[0], ud->date[1], ud->date[2], ud->date[3], ud->date[4]);
}

/*
	TODO add in-game :
	- pieces_catch ++ - pieces_loose ++ - pieces_moves ++
	- sp_tiles_use ++ - witch_formes ++

	TODO end of game : add win 1/0 loose + game_time_sec
*/
void	update_userdata(t_userdata *ud, int win, int game_time_sec)
{
	ud->total_game_time += game_time_sec;
	if (win)
		ud->nb_win += 1;
	else
		ud->nb_loose += 1;
	ud->average_game_time = _calc_average_game_time(ud);
	ud->winrate = _calc_winrate(ud->nb_win, ud->nb_loose);
	ud->xp = _calc_xp(ud);
	ud->lvl = _calc_lvl(ud->xp);
	_get_current_date(ud);
}

/* procedure

1. GET UD
2. play a game .. and add pieces_catch, sp_tiles_use, etc...
3. UPDATE UD with 1/0 and game_time_sec
4. SAVE UD
5. go to profil ..
6. GET UD with all updates , last date, etc...
*/
