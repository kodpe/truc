/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:12:10 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/13 18:03:46 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


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

static void	init_xpm(t_game *ga)
{
	t_2Dpt	pti;
	t_2Dvec	vci;
	int		i;

	pti = mx_pt(0, 0);
	vci = mx_vec(1, 1);
	i = 0;
	while (i < 12)
	{
		ga->xpm[i] = mx_init_img(ga->mlx_ptr, &ga->win, pti, vci);
		i++;
	}
}

static int	create_xpm(t_game *ga)
{
	if (mx_create_xpm_img(&ga->xpm[XPM_30W_LANTERN], XPM_PATH_30W_LANTERN))
		return (1);
	if (mx_create_xpm_img(&ga->xpm[XPM_80W_LANTERN], XPM_PATH_80W_LANTERN))
		return (1);
	if (mx_create_xpm_img(&ga->xpm[XPM_30W_LOTUS], XPM_PATH_30W_LOTUS))
		return (1);
	if (mx_create_xpm_img(&ga->xpm[XPM_80W_LOTUS], XPM_PATH_80W_LOTUS))
		return (1);
	if (mx_create_xpm_img(&ga->xpm[XPM_30W_MOUNTAIN], XPM_PATH_30W_MOUNTAIN))
		return (1);
	if (mx_create_xpm_img(&ga->xpm[XPM_80W_MOUNTAIN], XPM_PATH_80W_MOUNTAIN))
		return (1);
	if (mx_create_xpm_img(&ga->xpm[XPM_30W_CASTLE], XPM_PATH_30W_CASTLE))
		return (1);
	if (mx_create_xpm_img(&ga->xpm[XPM_80W_CASTLE], XPM_PATH_80W_CASTLE))
		return (1);
	if (mx_create_xpm_img(&ga->xpm[XPM_80W_SAMURAI], XPM_PATH_80W_SAMURAI))
		return (1);
	if (mx_create_xpm_img(&ga->xpm[XPM_80W_NINJA], XPM_PATH_80W_NINJA))
		return (1);
	if (mx_create_xpm_img(&ga->xpm[XPM_80W_DRAGON], XPM_PATH_80W_DRAGON))
		return (1);
	if (mx_create_xpm_img(&ga->xpm[XPM_80W_WITCH], XPM_PATH_80W_WITCH))
		return (1);
	return (0);
}

int	load_xpm(t_game *ga)
{
	init_xpm(ga);
	if (create_xpm(ga))
		return (1);
	return (0);
}

void	destroy_xpm(t_game *ga)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		mx_destroy_img(&ga->xpm[i]);
		i++;
	}
}
