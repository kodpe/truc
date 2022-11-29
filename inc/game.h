/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:26:53 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 15:18:07by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "mx.h"

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

# define PATH_COMDIR	"/sgoinfre/goinfre/Perso/sloquett/dcom/"
# define PATH_PHOTO		"/sgoinfre/photos_students/"
# define PATH_MAGICK	"/sgoinfre/goinfre/Perso/sloquett/tools/magick"

# define STR_START		"Game will start in  s"
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
	XPM_80W_LANTERN,
	XPM_30W_LOTUS,
	XPM_80W_LOTUS,
	XPM_30W_MOUNTAIN,
	XPM_80W_MOUNTAIN,
	XPM_30W_CASTLE,
	XPM_80W_CASTLE,
	XPM_80W_SAMURAI,
	XPM_80W_NINJA,
	XPM_80W_DRAGON,
	XPM_80W_WITCH,
}	t_xpmid;

typedef enum e_case_type
{
	CASE_NORMAL = 0,
	CASE_LANTERN = 1,
	CASE_LOTUS = 2,
	CASE_MOUNTAIN = 3,
	CASE_CASTLE = 4,
}	t_case_type;

typedef enum e_piece_t
{
	PIECE_SAMURAI = 5,
	PIECE_NINJA = 6,
	PIECE_DRAGON = 7,
	PIECE_WITCH = 8,
}	t_piece_t;

typedef struct s_piece
{
	t_piece_t	type;
	t_img		img;
	t_img		xpm;
	bool		owned;
	bool		mouseover;
}	t_piece;

typedef struct s_case
{
	t_case_type	type;
	t_aabb		abs_box;	// x,x 160,160
	t_aabb		rel_box;	// 0,0 160,160

	t_piece		*piece;
	// NULL if the case is empty

	bool		mouseover;
	bool		visible;
	// si le joueur a une piece sur la case 
	//ou si elle est eclairée
}	t_case;

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

typedef struct s_gameinfo
{
	t_img	img;
	char	*txt;
}	t_gameinfo;

typedef struct s_waiting_box
{
	t_img	img;
	int		i;
	int		starting_delay;
}	t_waiting_box;

typedef struct s_txt_input
{
	t_img	img;
	char	*buffer;
	int		size_x;
	int		maxlen;
	int		len;
}	t_txt_input;

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
	int		average_turn_time;
	int		last_gane_date;
}	t_userdata;

typedef struct s_game
{
	bool	server;
	bool	client;
	bool	solo;

	void	*mlx_ptr;
	t_win	win;
	t_profil	profil_opp;
	t_profil	profil_you;

	//? ** LOOP MEMU ** //
	t_loop			lp_menu;
	t_but			bt_play;
	t_but			bt_quit;
	t_but			bt_profil;

	//? ** LOOP WAITOPP ** //
	t_loop			lp_waitopp;

	//? ** LOOP STARTGAME ** //
	t_loop			lp_startgame;

	//? ** LOOP PROFIL ** //
	t_loop			lp_profil;
	t_userdata		ud;

	//? ** LOOP GAME ** //
	t_loop			lp_game;


//END 
	t_evstat		evstat;


	t_txt_input		txi;

	// used in waitopp, startgame, wantquit
	t_waiting_box	waitbox;
	t_img			testborder;
	t_img			testborder2;
	t_img			testborder3;

	t_but 			bt;

	t_gameinfo	info;

	t_img	img_board;
	t_case	board[5][5];

	t_img	xpm[12];
	t_piece	piece[8];

	t_2Dpt	mouse;
}	t_game;

/* COM */
int		server_exist(void);
void	create_server(t_game *ga);
void	sc_check_multiplayer(t_game *ga);
void	receive_opponent(t_game *ga);
void	create_client(t_game *ga);
/* COM UTILS */
void	log_com(t_game *ga);
char	*get_username(void);
char	*get_username_code(void);
char	*set_username_code(char *name);
char	*get_opponent_file(char	*player_file);
char	*parse_opponent_name(char *opp_file);
char	*create_comfile(char *file);
char	*get_user_photo(char *username);
int		resize_img(char *src_path, char *dest_path, t_2Dvec size_max);
char	*get_42position(void);
int		assert_comfile(char *path);
int		com_send(char *path, char *msg);
char	*com_receive(char *path);
/* DIR */
void	dir_log(char *dirpath);
int		dir_size(char *dirpath);
char	**dir_namelist(char *dirpath);

/* LOOP */
# define LOOP_START			-1
# define LOOP_EXIT			0
# define LOOP_ID_MENU		100
# define LOOP_ID_WAITOPP	101
# define LOOP_ID_STARTGAME	102
# define LOOP_ID_PROFIL		103
# define LOOP_ID_GAME		200

void	loop_menu(t_game *ga);
void	loop_profil(t_game *ga);

void	loop_waitopp(t_game *ga);
void	loop_startgame(t_game *ga);

void	loop_game(t_game *ga);

/* LOOP UTILS */
int		loop_manager(t_game *ga);
void	goto_loop(t_game *ga, int src_id, int dest_id);

/* LOOP GAME ONLY */
int		load_xpm(t_game *ga);
void	destroy_xpm(t_game *ga);

void	load_profils(t_game	*ga);
void	destroy_profil(t_profil *profil);

#endif /* GAME_H */
