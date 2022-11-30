/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_userdata.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:00:24 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/30 01:24:15 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// int date[5]; // h:m D/M/Y
char	*_get_str_date(t_userdata *ud)
{
	char	*date;

	date = ft_calloc(sizeof(char) * 41);
	if (!date)
		abort();
	snprintf(date, 40, "%02d:%02d %02d/%02d/%04d", \
		ud->date[0], ud->date[1], ud->date[2], ud->date[3], ud->date[4]);
	// 15:02 09/02/2022
#if 0
	LOG
	dprintf(2, "DATE tab [%02d:%02d %02d/%02d/%04d]\n", \
		ud->date[0], ud->date[1], ud->date[2], ud->date[3], ud->date[4]);
	dprintf(2, "DATE str [%s]\n", date);
#endif
	return (date);
}

static t_userdata	_fill_userdata(char **sp)
{
	t_userdata	ud;

	if (ft_arlen(sp) != 38)
	{
		ft_putarray(sp);
		abort();
	}
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
		ud.pieces_catch[i] = ft_atoi(sp[7 + i]);
		ud.pieces_loose[i] = ft_atoi(sp[11 + i]);
		ud.pieces_moves[i] = ft_atoi(sp[15 + i]);
		ud.sp_tiles_use[i] = ft_atoi(sp[19 + i]);
	}
	for (int i = 0; i < 8; i++)
		ud.witch_formes[i] = ft_atoi(sp[23 + i]);
	ud.total_game_time = ft_atoi(sp[31]);
	ud.average_game_time = ft_atoi(sp[32]);
	for (int i = 0; i < 5; i++)
		ud.date[i] = ft_atoi(sp[33 + i]);
	ud.str_date = _get_str_date(&ud);
	// show_userdata(&ud, sp);
	return (ud);
}

static t_userdata	_default_userdata(void)
{
	t_userdata	ud;

	ft_memset(&ud, 0, sizeof(t_userdata));
	ud.name = ft_strdup(getenv("USER"));
	if (!ud.name)
		abort();
	ud.personal_user_photo = ft_strdup("no_photo_path");
	ud.str_date = ft_strdup("no_str_date");
	return (ud);
}

t_userdata	get_userdata(void)
{
	char		*path;
	int			fd;
	char		*line;
	char		**sp;
	t_userdata	ud;

	LOG
	path = ft_strjointri(PATH_USERDATA, getenv("USER"), ".ud");
	if (!path)
		abort();
	fd = open(path, O_CREAT | O_RDONLY, 0666);
	if (fd == -1)
		abort();
	free(path);
	line = get_next_line(fd);
	ft_close_gnl(fd);
	close(fd);
	// c_bold(); c_red(); printf("LINE [%s]\n", line); c_reset(); //!
	// LOG
	// getchar(); //!

	if (!line)
		return (_default_userdata());
	sp = ft_split(line, ' ');
	// show_userdata(NULL, sp);
	free(line);
	if (!sp)
		abort();
	ud = _fill_userdata(sp);
	ft_arfree(sp);
	// show_userdata(&ud, NULL);
	return (ud);
}

/* procedure

1. GET UD
2. play a game .. and add pieces_catch, sp_tiles_use, etc...
3. UPDATE UD with 1/0 and game_time_sec
4. SAVE UD
5. go to profil ..
6. GET UD with all updates , last date, etc...
*/
