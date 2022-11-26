/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:26:53 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/26 03:17:25 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "mx.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# define PATH_COMDIR	"/sgoinfre/goinfre/Perso/sloquett/dcom/"
# define PATH_PHOTO		"/sgoinfre/photos_students/"
# define PATH_MAGICK	"/sgoinfre/goinfre/Perso/sloquett/tools/magick"

# define STR_START	"Game will start in  s"
# define STR_WAIT	"Waiting for an opponent"

# define SERVER_NAME	"clvicent"
# define CLIENT_NAME	"chsimon"

// # define STOP_AFTER_INIT

# define MULTIPLAYER

# undef SOLO
# ifndef MULTIPLAYER
#  define SOLO
# endif

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

// you current player / opp opponent
typedef struct s_game
{
	bool	server;
	bool	client;
	bool	solo;
	bool	room_wait; //
	bool	room_start; //
	bool	room_game; //

	t_waiting_box	waitbox;

	void	*mlx_ptr;
	t_win	win;

	t_profil	profil_opp;
	t_profil	profil_you;
	t_gameinfo	info;

	t_img	img_board;
	t_case	board[5][5];

	t_img	xpm[12];
	t_piece	piece[8];

	t_2Dpt	mouse;
}	t_game;

void	game_init(t_game *ga);

/* COM */
int		server_exist(void);
void	create_server(t_game *ga);
void	create_client(t_game *ga);
void	receive_opponent(t_game *ga);
/* COM UTILS */
void	log_com(t_game *ga);
char	*get_username(void);
char	*get_username_code(void);
char	*set_username_code(char *name);
char	*get_opponent_file(char	*player_file);
char	*parse_opponent_name(char *opp_file);
void	create_comfile(char *path);
char	*get_user_photo(char *username);
int		resize_img(char *src_path, char *dest_path, t_2Dvec size_max);
char	*get_42position(void);
int		assert_comfile(char *comfile_path);

// MAIN LOOP

void	main_loop(t_game *ga);

int		load_xpm(t_game *ga);
void	destroy_xpm(t_game *ga);

////
void	destroy_profil(t_profil *profil);
void	load_profils(t_game	*ga);

// dir
void	dir_log(char *dirpath);
int		dir_size(char *dirpath);
char	**dir_namelist(char *dirpath);

void	lobby_room(t_game *ga);
int		loop_waiting(t_game *ga);
int		loop_starting(t_game *ga);
void	lobby_exit(t_game *ga);

#endif /* GAME_H */
