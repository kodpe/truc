/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:58:19 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/26 13:15:54 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	lobby_exit(t_game *ga)
{
	unlink_sc(ga->profil_you.path);
	free(ga->profil_you.file);
	free(ga->profil_you.name);
	free(ga->profil_you.path);
	free(ga->profil_opp.file);
	free(ga->profil_opp.name);
	free(ga->profil_opp.path);
	mx_destroy_img(&ga->waitbox.img);
	mx_destroy_win(&ga->win);
	mx_destroy_mlx(ga->mlx_ptr);
}
