/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profil_init_txt_part.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:16:45 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/30 02:17:49 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	profil_init_txt_part(t_game *ga)
{
	t_img	img;
	t_2Dpt	origin;
	t_2Dvec	size;

	size = mx_vec(ga->win.width - 20, 200);
	origin = mx_pt(10, 10);
	img = mx_init_img(ga->mlx_ptr, &ga->win, origin, size);
	if (mx_create_img(&img, "txt_part"))
		abort();
	// mx_draw_box_img(&img, DARK_GRAY);
	mx_draw_img(&img);

	t_userdata	*ud = &ga->ud;
	char	*tmp;

	tmp = ft_strjoin("<> NAME    : ", ud->name);
	mx_putstr_img(&img, mx_pt(20, 20), tmp, SILVER);
	free(tmp);

	mx_putstr_cen_img(&img, ft_strtoupper(ud->name), SILVER, -size.y / 2 + 55);
	// mx_putstr_cen_img(&img, "Rank ", SILVER, -size.y / 2 + 95);

	tmp = ft_itoa(ud->lvl);
	char *tmp_lvl = ft_strjoin("<> LVL     : ", tmp);
	free(tmp);
	mx_putstr_img(&img, mx_pt(20, 40), tmp_lvl, SILVER);
	free(tmp_lvl);

	tmp = ft_itoa(ud->xp);
	char *tmp_xp1 = ft_strjointri("<> XP      : ", tmp, " / ");
	free(tmp);
	tmp = ft_itoa(ft_power(2, ud->lvl));
	char *tmp_xp = ft_strjoin(tmp_xp1, tmp);
	free(tmp_xp1);
	free(tmp);
	mx_putstr_img(&img, mx_pt(20, 60), tmp_xp, SILVER);
	free(tmp_xp);

	tmp = ft_itoa(ud->total_game_time);
	char *tmp_tt = ft_strjointri("<> Total playing time    : ", tmp, "s");
	free(tmp);
	mx_putstr_img(&img, mx_pt(20, 80), tmp_tt, SILVER);
	free(tmp_tt);

	tmp = ft_itoa(ud->average_game_time);
	char *tmp_av = ft_strjointri("<> Average game duration : ", tmp, "s");
	free(tmp);
	mx_putstr_img(&img, mx_pt(20, 100), tmp_av, SILVER);
	free(tmp_av);

	tmp = ft_strjoin("<> Optional photo : ", ud->personal_user_photo);
	mx_putstr_img(&img, mx_pt(20, 160), tmp, SILVER);
	free(tmp);

	tmp = ft_strjoin("<> Last game      : ", ud->str_date);
	mx_putstr_img(&img, mx_pt(20, 180), tmp, SILVER);
	free(tmp);

	tmp = ft_itoa(ud->nb_win);
	char *tmp_win = ft_strjoin("<> WINS : ", tmp);
	free(tmp);
	tmp = ft_itoa(ud->nb_loose);
	char *tmp_loo = ft_strjoin("   <> LOOSES : ", tmp);
	free(tmp);
	tmp = ft_itoa(ud->winrate);
	char *tmp_rat = ft_strjointri("   <> WINRATE : ", tmp, "%");
	free(tmp);
	tmp = ft_strjointri(tmp_win, tmp_loo, tmp_rat);
	free(tmp_win);
	free(tmp_loo);
	free(tmp_rat);
	mx_putstr_cen_img(&img, tmp, SILVER, -size.y / 2 + 15);
	free(tmp);

	mx_destroy_img(&img);
}
