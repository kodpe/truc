/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:22:17 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 12:22:49 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

void	mx_putstr_img(t_img *img, t_2Dpt origin, char *str, t_uint hexcolor)
{
	if (!str)
		return ;
	mlx_string_put(img->mlx_ptr, img->win->ptr, \
					origin.x, origin.y, \
					hexcolor, str);
}

void	mx_putstr_cen_img(t_img *img, char *str, t_uint hexcolor, int align_y)
{
	int	offset;

	if (!str)
		return ;
	offset = (ft_strlen(str) * 6);
	if (img->width - offset < 1)
	{
		mlx_string_put(img->mlx_ptr, img->win->ptr, \
						img->origin.x + 20, img->origin.y + 20, \
						RED, "[err:str too long]");
		return ;
	}
	int	font_height = 10; // font witdh = 6 (default mlx font 6 x 10)
	align_y += font_height / 2;
	mlx_string_put(img->mlx_ptr, img->win->ptr, \
					img->origin.x + img->width / 2 - offset / 2, \
					img->origin.y + img->height / 2 + align_y, \
					hexcolor, str);
}

void	mx_putnbr_img(t_img *img, t_2Dpt origin, int nbr, t_uint hexcolor)
{
	char	*str;

	str = ft_itoa(nbr);
	if (!str)
		return ;
	mx_putstr_img(img, origin, str, hexcolor);
	free(str);
}

void	mx_putnbr_cen_img(t_img *img, int nbr, t_uint hexcolor)
{
	char	*str;

	str = ft_itoa(nbr);
	if (!str)
		return ;
	mx_putstr_cen_img(img, str, hexcolor, 0);
	free(str);
}
