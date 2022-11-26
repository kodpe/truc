/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:58:19 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/25 23:14:14 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	lobby_exit(t_game *ga)
{
	char	*comfilepath = ft_strjoin(PATH_COMDIR, ga->profil_you.file);
	unlink_sc(comfilepath);
	free(comfilepath);
	if (ga->profil_you.file)
		free(ga->profil_you.file);
	if (ga->profil_you.name)
		free(ga->profil_you.name);
	if (ga->profil_opp.file)
		free(ga->profil_opp.file);
	if (ga->profil_opp.name)
		free(ga->profil_opp.name);
	mx_destroy_img(&ga->waitbox.img);
	mx_destroy_win(&ga->win);
	mx_destroy_mlx(ga->mlx_ptr);
}
