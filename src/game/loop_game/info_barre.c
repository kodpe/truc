/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_barre.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:56:36 by sloquet           #+#    #+#             */
/*   Updated: 2022/12/03 00:06:25 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	put_info(t_game *ga, char *new_msg)
{
	if (ft_strcmp(ga->info.txt, new_msg))
	{
		free(ga->info.txt);
		ga->info.txt = ft_strdup(new_msg);
	}
}

void	destroy_info(t_game *ga)
{
	free(ga->info.txt);
	free(ga->info.oldtxt);
	mx_destroy_img(&ga->info.img);
}

void	create_info(t_game *ga)
{
	t_2Dpt pos;

	pos = mx_pt(200, 800);
	ga->info.img = mx_init_img(ga->mlx_ptr, &ga->win, pos, mx_vec(800, 100));
	if (mx_create_img(&ga->info.img, "game info"))
		abort();
	mx_draw_aabb(&ga->info.img, ga->info.img.box_rel, RED);

	ga->info.txt = ft_strdup("bonjour je suis le texte numero 1 d'une certaine longueur hehe");
	ga->info.oldtxt = ft_strdup(ga->info.txt);
	mx_draw_img(&ga->info.img);
	mx_putstr_cen_img(&ga->info.img, ga->info.txt, SILVER, 0);
}

void	update_info(t_game *ga)
{
	if (ft_strcmp(ga->info.txt, ga->info.oldtxt))
	{
		mx_draw_img(&ga->info.img);
		mx_putstr_cen_img(&ga->info.img, ga->info.txt, SILVER, 0);
		free(ga->info.oldtxt);
		ga->info.oldtxt = ft_strdup(ga->info.txt);
	}
}
