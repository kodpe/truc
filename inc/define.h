/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:40:50 by sloquet           #+#    #+#             */
/*   Updated: 2022/12/02 23:29:40 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DEFINE_H
# define DEFINE_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# define PATH_USERDATA	"/sgoinfre/goinfre/Perso/sloquett/udat/"
# define PATH_COMDIR	"/sgoinfre/goinfre/Perso/sloquett/dcom/"
# define PATH_PHOTO		"/sgoinfre/photos_students/"
# define PATH_MAGICK	"/sgoinfre/goinfre/Perso/sloquett/tools/magick"

# define STR_START		"Game will start in "
# define STR_WAIT		"Waiting for an opponent"
# define STR_WANTQUIT	"Are you sure you want to quit?"
# define STR_WANTLOSE	"You will lose this game"

# define SERVER_NAME	"eleotard"
# define CLIENT_NAME	"eamar"

# define COM_VERBOSE
# define COM_TRUNC_RECEIVE
# define COM_IGNORE_EMPTY_RECEIVE


#define XPM_PATH_30W_LANTERN	"assets/30w_xpm/30w_lantern.xpm"
#define XPM_PATH_30W_LOTUS		"assets/30w_xpm/30w_lotus.xpm"
#define XPM_PATH_30W_MOUNTAIN	"assets/30w_xpm/30w_mountain.xpm"
#define XPM_PATH_30W_CASTLE		"assets/30w_xpm/30w_castle.xpm"
#define XPM_PATH_30W_SAMURAI	"assets/30w_xpm/30w_samurai.xpm"
#define XPM_PATH_30W_NINJA		"assets/30w_xpm/30w_ninja.xpm"
#define XPM_PATH_30W_DRAGON		"assets/30w_xpm/30w_dragon.xpm"
#define XPM_PATH_30W_WITCH		"assets/30w_xpm/30w_witch.xpm"

#define XPM_PATH_80W_LANTERN	"assets/80w_xpm/80w_lantern.xpm"
#define XPM_PATH_80W_LOTUS		"assets/80w_xpm/80w_lotus.xpm"
#define XPM_PATH_80W_MOUNTAIN	"assets/80w_xpm/80w_mountain.xpm"
#define XPM_PATH_80W_CASTLE		"assets/80w_xpm/80w_castle.xpm"
#define XPM_PATH_80W_SAMURAI	"assets/80w_xpm/80w_samurai.xpm"
#define XPM_PATH_80W_NINJA		"assets/80w_xpm/80w_ninja.xpm"
#define XPM_PATH_80W_DRAGON		"assets/80w_xpm/80w_dragon.xpm"
#define XPM_PATH_80W_WITCH		"assets/80w_xpm/80w_witch.xpm"

typedef enum e_xpmid
{
	XPM_30W_LANTERN,
	XPM_30W_LOTUS,
	XPM_30W_MOUNTAIN,
	XPM_30W_CASTLE,
	XPM_80W_LANTERN,
	XPM_80W_LOTUS,
	XPM_80W_MOUNTAIN,
	XPM_80W_CASTLE,
	XPM_80W_SAMURAI,
	XPM_80W_NINJA,
	XPM_80W_DRAGON,
	XPM_80W_WITCH,
}	t_xpmid;

typedef enum e_case_type
{
	CASE_NORMAL = 0,
	CASE_LANTERN = 4,
	CASE_LOTUS,
	CASE_MOUNTAIN,
	CASE_CASTLE,
}	t_case_type;

typedef enum e_piece_t
{
	PIECE_SAMURAI = 8,
	PIECE_NINJA,
	PIECE_DRAGON,
	PIECE_WITCH,
}	t_piece_t;

typedef struct s_profil
{
	t_img	img;
	char	*name;
	char	*file;
	char	*path;
	t_img	photo;
	char	*photo_path;
	char	*photo_xpm_tmp_path;
	char	*gps;
}	t_profil;

typedef struct s_waiting_box
{
	t_img	img;
	int		i;
	int		starting_delay;
}	t_waiting_box;

typedef struct s_userdata
{
	char	*name;
	char	*personal_user_photo;
	int		lvl;
	int		xp;
	int		nb_win;
	int		nb_loose;
	int		winrate;
	int		pieces_catch[4];	 	//! F N W D
	int		pieces_loose[4];		//!"
	int		pieces_moves[4];		//!"
	int		sp_tiles_use[4];		// ! L U C M
	int		witch_formes[8];		// ! F L N U W C D M
	int		total_game_time;
	int		average_game_time;
	int		date[5];				// h:m D/M/Y
	char	*str_date;
}	t_userdata;

#endif /* DEFINE_H */
