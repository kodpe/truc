/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:50:15 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/24 15:20:22 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

bool	mx_sc_pixel_outside_img(t_img *img, int x, int y)
{
	t_aabb	imgbox;

	imgbox.origin = mx_pt(0, 0);
	imgbox.lenght = mx_vec(img->width, img->height);
	if (mx_coll_xy_aabb(x, y, imgbox))
		return (false);
	return (true);
}

void	mx_draw_pixel(t_img *img, int x, int y, t_uint hexcolor)
{
	char	*dest;
	int		offset;

	if (mx_sc_pixel_outside_img(img, x, y))
		abort();
	offset = y * img->size_line + x * (img->bits_per_pixel / 8);
	dest = img->addr + offset;
	*(t_uint *)dest = hexcolor;
}

t_uint	mx_get_pixel_color(t_img *img, int x, int y)
{
	char	*dest;
	int		offset;
	t_uint	color;

	if (mx_sc_pixel_outside_img(img, x, y))
		abort();
	offset = y * img->size_line + x * (img->bits_per_pixel / 8);
	dest = img->addr + offset;
	color = *(t_uint *)dest;
	return (color);
}
