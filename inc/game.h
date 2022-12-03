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
# include "define.h"

typedef struct s_piece
{
	t_piece_t	type;
	t_but		bt;
}	t_piece;

typedef struct s_case
{
	t_case_type	type;
	t_but		bt;
	t_piece		*piece; // piece ptr, NULL if the case is empty
	t_2Dpt		case_id;
}	t_case;

typedef struct s_gameinfo
{
	t_img	img;
	t_img	img1;
	t_img	img2;
	char	*txt;
	char	*oldtxt;
}	t_gameinfo;

typedef struct s_game
{
	bool			server;
	bool			client;
	void			*mlx_ptr;
	t_win			win;
	t_evstat		evstat;
	t_profil		profil_opp;
	t_profil		profil_you;

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
	t_but			pbt_pc_catch;
	t_but			pbt_pc_loose;
	t_but			pbt_pc_moves;
	t_but			pbt_sp_tiles;
	t_but			pbt_wi_forme;

	//? ** LOOP GAME ** //
	t_loop			lp_game;

	// used in waitopp, startgame
	t_waiting_box	waitbox;

	// used in game loop
	t_img			xpm[12];
	t_gameinfo		info;

	t_but			fullboard;
	t_case			board[5][5];
	t_piece			pc;

}	t_game;

void	create_board(t_game *ga);
void	destroy_board(t_game *ga);
void	update_board(t_game *ga);

void	destroy_piece(t_game *ga);
void	update_piece(t_game *ga);
void	create_piece(t_game *ga);

void	put_info(t_game *ga, char *new_msg);
void	destroy_info(t_game *ga);
void	create_info(t_game *ga);
void	update_info(t_game *ga);

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
/* USERDATA */
void		destroy_userdata(t_userdata *ud);
t_userdata	get_userdata(void);
void		save_userdata(t_userdata *ud, char *name);
void		show_userdata(t_userdata *ud, char **sp);
void		update_userdata(t_userdata *ud, int win, int game_time_sec);

/* LOOP */
# define LOOP_START			-1
# define LOOP_EXIT			0
# define LOOP_ID_MENU		100
# define LOOP_ID_WAITOPP	101
# define LOOP_ID_STARTGAME	102
# define LOOP_ID_PROFIL		103
# define LOOP_ID_GAME		200

//? ** LOOP MEMU ** //
void	loop_menu(t_game *ga);

//? ** LOOP PROFIL ** //
void	loop_profil(t_game *ga);
void	profil_init_graph(t_game *ga, int index_data_graph);
void	profil_init_graph_but(t_game *ga);
void	profil_init_txt_part(t_game *ga);
void	profil_graph_actions(t_game *ga);

//? ** LOOP WAITOPP ** //
void	loop_waitopp(t_game *ga);

//? ** LOOP STARTGAME ** //
void	loop_startgame(t_game *ga);

//? ** LOOP GAME ** //
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
