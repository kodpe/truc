/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 02:06:56 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/11 13:39:50 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SMLX_H
# define SMLX_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"

int		smlx_new_xpm(t_smlx *mlx, t_img *img, char *file, int id);

int		smlx_new_image(t_smlx *mlx, int id, int width, int height);
int		smlx_new_window(t_smlx *mlx, int id, int width, int height);

int		smlx_init(t_smlx *mlx, int nb_img);

int		smlx_reload(t_smlx *mlx, int nb_img);
void	smlx_destroy_image(t_smlx *mlx, t_img *img);
void	smlx_destroy(t_smlx *mlx);
void	smlx_display_image(t_smlx *mlx, int id, int x, int y);
int		smlx_reset_image(t_smlx *mlx, int id);
t_2Dpnt	smlx_pos(int x, int y);
void	smlx_box_img(t_img *img, t_2Dpnt origin, int hexcolor);
void	smlx_box_max(t_img *img, t_2Dpnt origin, t_2Dpnt max, int hexcolor);
void	smlx_box_len(t_img *img, t_2Dpnt origin, t_2Dpnt len, int hexcolor);
void	smlx_hline(t_img *img, t_2Dpnt origin, int len, int hexcolor);
void	smlx_vline(t_img *img, t_2Dpnt origin, int len, int hexcolor);
void	smlx_screen_filler(t_img *img, int hexcolor);
void	smlx_grid(t_img *img, t_2Dpnt origin, t_2Dpnt len, t_2Dpnt nbcases, int hexcolor);
void	smlx_circle_center(t_img *img, t_2Dpnt center , int radius, int hexcolor);
void	smlx_circle_topleft(t_img *img, t_2Dpnt origin , int radius, int hexcolor);

#endif
