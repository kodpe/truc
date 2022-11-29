/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profil.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:42:59 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 11:44:43 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	destroy_profil(t_profil *profil)
{
	if (profil->path)
		unlink_sc(profil->path);
	free(profil->name);
	free(profil->file);
	free(profil->path);
	free(profil->gps);
	free(profil->photo_path);
	if (profil->photo_xpm_tmp_path)
		unlink_sc(profil->photo_xpm_tmp_path);
	free(profil->photo_xpm_tmp_path);
	mx_destroy_img(&profil->img);
	mx_destroy_img(&profil->photo);
	ft_memset(profil, 0, sizeof(t_profil));
}

static void	load_profil_photo(t_game *ga, t_profil *profil, t_2Dpt origin)
{
	char	*dest_path;
	t_2Dpt	img_origin;

	img_origin = mx_pt(origin.x + 5, origin.y + 1);
	profil->photo = mx_init_img(ga->mlx_ptr, &ga->win, img_origin, mx_vec(100, 67));
	assert(profil->name);
	profil->photo_path = get_user_photo(profil->name);
	if (profil->photo_path)
	{
		dest_path = ft_strjointri("/tmp/", profil->file, ".xpm");
		if (!dest_path)
			abort();
		if (0 == resize_img(profil->photo_path, dest_path, mx_vec(100, 100)))
		{
			if (mx_create_xpm_img(&profil->photo, dest_path))
				abort();
			profil->photo_xpm_tmp_path = dest_path;
			mx_draw_aabb(&profil->photo, profil->photo.box_rel, RED);
			mx_draw_img(&profil->photo);
			return ;
		}
		profil->photo_xpm_tmp_path = NULL;
		free(dest_path);
	}
	if (mx_create_img(&profil->photo, "unfound profil photo"))
		abort();
	mx_fill_img(&profil->photo, DARK_GRAY);
	mx_draw_aabb(&profil->photo, profil->photo.box_rel, RED);
	mx_draw_img(&profil->photo);
	mlx_string_put(ga->mlx_ptr, ga->win.ptr, \
		profil->photo.origin.x + 47, profil->photo.origin.y + 37, WHITE, "?");
}

static void	put_profil_info(t_game *ga, t_profil *profil, t_2Dpt origin)
{
	t_2Dpt	pos;

	pos = mx_pt(origin.x + 10, origin.y + 80);
	assert(profil->name);
	mlx_string_put(ga->mlx_ptr, ga->win.ptr, pos.x, pos.y, SILVER, profil->name);
	profil->gps = get_42position();
	pos = mx_pt(origin.x + 10, origin.y + 95);
	mlx_string_put(ga->mlx_ptr, ga->win.ptr, pos.x, pos.y, SILVER, profil->gps);
}

void	load_profils(t_game	*ga)
{
	t_2Dpt you;
	t_2Dpt opp;

	/**	YOU	**/
	you = mx_pt(0, 700);
	ga->profil_you.img = mx_init_img(ga->mlx_ptr, &ga->win, you, mx_vec(200, 100));
	if (mx_create_img(&ga->profil_you.img, "profil_you"))
		abort();
	mx_draw_aabb(&ga->profil_you.img, ga->profil_you.img.box_rel, RED);
	mx_draw_img(&ga->profil_you.img);
	load_profil_photo(ga, &ga->profil_you, you);
	put_profil_info(ga, &ga->profil_you, you);

	/** OPPONENT **/
	opp = mx_pt(1000, 0);
	ga->profil_opp.img = mx_init_img(ga->mlx_ptr, &ga->win, opp, mx_vec(200, 100));
	if (mx_create_img(&ga->profil_opp.img, "profil_opp"))
		abort();
	mx_draw_aabb(&ga->profil_opp.img, ga->profil_opp.img.box_rel, RED);
	mx_draw_img(&ga->profil_opp.img);
	load_profil_photo(ga, &ga->profil_opp, opp);
	put_profil_info(ga, &ga->profil_opp, opp);
}
