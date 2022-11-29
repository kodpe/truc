/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_userdata.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:33:40 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 18:38:46 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void _update_average_turn_time(t_userdata *ud, int one_turn_time)
{
	ud->average_turn_time =  one_turn_time; // TODO c cassé
}

static void	_update_average_game_time(t_userdata *ud)
{
	ud->average_game_time = ud->total_game_time / (ud->nb_win + ud->nb_loose);
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
	dprintf(2, "LVL [%i]\m", i);
	return (i);
}

static int	_calc_winrate(int win, int loose)
{
	return (win * 100 / (win + loose));
}

char	*get_txt_date(t_userdata *ud)
{
	char	*date;

	date = ft_calloc(sizeof(char) * 41);
	if (!date)
		abort();
	snprintf(date, 40, "%i:%i %i/%i/%i", \
		ud->date[0], ud->date[1], ud->date[2], ud->date[3], ud->date[4]);
	// 15:42 9/2/2022
	dprintf(2, "DATE [%s]\m", date);
	return (date);
}

/*
	t_userdata *ud and char **sp can be null
*/
void	show_user_data(t_userdata *ud, char **sp)
{
	if (sp)
		ft_putarray(sp);
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
		dprintf(2, "%i: pieces_catch %i:[%i]\n", 8+i, i, ud->pieces_catch[i]);
	for (int i = 0; i < 4; i++)
		dprintf(2, "%i: pieces_loose %i:[%i]\n", 12+i, i, ud->pieces_loose[i]);
	for (int i = 0; i < 4; i++)
		dprintf(2, "%i: pieces_moves %i:[%i]\n", 16+i, i, ud->pieces_moves[i]);
	for (int i = 0; i < 4; i++)
		dprintf(2, "%i: sp_tiles_use %i:[%i]\n", 20+i, i, ud->sp_tiles_use[i]);
	for (int i = 0; i < 8; i++)
		dprintf(2, "%i: witch_formes %i:[%i]\n", 24+i, i, ud->witch_formes[i]);
	dprintf(2, "32: total_game_time   [%i]\n", ud->total_game_time);
	dprintf(2, "33: average_game_time [%i]\n", ud->average_game_time);
	dprintf(2, "34: average_turn_time [%i]\n", ud->average_turn_time);
	for (int i = 0; i < 5; i++)
		dprintf(2, "%i: date %i:[%i]\n", 35+i, i, ud->date[i]);
}

static t_userdata	_fill_userdata(char **sp)
{
	t_userdata	ud;

	ft_memset(&ud, 0, sizeof(t_userdata));
	ud.name = ft_strdup(sp[0]);
	if (!ud.name)
		abort();
	ud.personal_user_photo = ft_strdup(sp[1]);
	ud.lvl = ft_atoi(sp[2]);
	ud.xp = ft_atoi(sp[3]);
	ud.nb_win = ft_atoi(sp[4]);
	ud.nb_loose = ft_atoi(sp[5]);
	ud.winrate = ft_atoi(sp[6]);
	for (int i = 0; i < 4; i++)
	{
		ud.pieces_catch[i] = ft_atoi(sp[8 + i]);
		ud.pieces_loose[i] = ft_atoi(sp[12 + i]);
		ud.pieces_moves[i] = ft_atoi(sp[16 + i]);
		ud.sp_tiles_use[i] = ft_atoi(sp[20 + i]);
	}
	for (int i = 0; i < 8; i++)
		ud.witch_formes[i] = ft_atoi(sp[24 + i]);
	ud.total_game_time = ft_atoi(sp[32]);
	ud.average_game_time = ft_atoi(sp[33]);
	ud.average_turn_time = ft_atoi(sp[34]);
	for (int i = 0; i < 5; i++)
		ud.date[i] = ft_atoi(sp[35 + i]);
	return (ud);
}

static t_userdata	_default_userdata(void)
{
	t_userdata	ud;

	ft_memset(&ud, 0, sizeof(t_userdata));
	ud.name = ft_strdup("no_name");
	ud.personal_user_photo = ft_strdup("no_photo_path");
	return (ud);
}

void	save_userdata(t_userdata *ud, char *name)
{
	char	*path;

	assert(name);
	path = ft_strjointri(PATH_USERDATA, name, ".ud");
	if (!path)
		abort();
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		abort();
	free(path);
	dprintf(fd, " %s %s", ud->name, ud->personal_user_photo);
	dprintf(fd, " %i %i", ud->lvl, ud->xp);
	dprintf(fd, " %i %i %i", ud->nb_win, ud->nb_loose, ud->winrate);
	for (int i = 0; i < 4; i++)
		dprintf(fd, " %i", ud->pieces_catch[i]);
	for (int i = 0; i < 4; i++)
		dprintf(fd, " %i", ud->pieces_loose[i]);
	for (int i = 0; i < 4; i++)
		dprintf(fd, " %i", ud->pieces_moves[i]);
	for (int i = 0; i < 4; i++)
		dprintf(fd, " %i", ud->sp_tiles_use[i]);
	for (int i = 0; i < 8; i++)
		dprintf(fd, " %i", ud->witch_formes[i]);
	dprintf(fd, " %i", ud->total_game_time);
	dprintf(fd, " %i", ud->average_game_time);
	dprintf(fd, " %i", ud->average_turn_time);
	for (int i = 0; i < 5; i++)
		dprintf(fd, " %i", ud->date[i]);
	dprintf(fd, "\n");
	close(fd);
}

t_userdata	get_userdata(char *name)
{
	char		*path;
	int			fd;
	char		*line;
	char		**sp;
	t_userdata	ud;

	assert(name);
	path = ft_strjointri(PATH_USERDATA, name, ".ud");
	if (!path)
		abort();
	fd = open(path, O_CREAT | O_RDONLY, 0666);
	if (fd == -1)
		abort();
	free(path);
	line = get_next_line(fd);
	ft_close_gnl(fd);
	close(fd);
	if (!line)
		return (_default_userdata());
	sp = ft_split(line);
	free(line);
	if (!sp)
		abort();
	ud = _fill_userdata(sp);
	ft_arfree(sp);
	return (ud);
}
