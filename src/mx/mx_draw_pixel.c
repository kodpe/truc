/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:50:15 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/12 04:16:12 by sloquet          ###   ########.fr       */
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

void	mx_draw_pixel(t_img *img, int x, int y, int hex_color)
{
	char			*dest;
	int				offset;
	unsigned int	color;

	if (mx_sc_pixel_outside_img(img, x, y))
		abort();
	color = hex_color;
	offset = y * img->size_line + x * (img->bits_per_pixel / 8);
	dest = img->addr + offset;
	*(unsigned int *)dest = color;
}
