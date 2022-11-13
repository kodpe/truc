/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:15:53 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/13 17:24:54 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

#undef MX_NAME
#define MX_NAME "mx_init_img()"

t_img	mx_init_img(void *mlx_ptr, t_win *win, t_2Dpt origin, t_2Dvec size)
{
	t_img	img;

	ft_memset(&img, 0, sizeof(t_img));
	img.origin.x = origin.x;
	img.origin.y = origin.y;
	img.width = size.x;
	img.height = size.y;
	img.mlx_ptr = mlx_ptr;
	img.win = win;
	mx_log_img(MX_NAME, &img);
	return (img);
}

#undef MX_NAME
#define MX_NAME "mx_create_img()"

int	mx_create_img(t_img *img, char *name)
{
	mx_log_img(MX_NAME, img);
	if (img->width < 1 || img->height < 1)
		return (1);
	img->name = ft_strdup(name);
	if (!img->name)
		return (1);
	img->ptr = mlx_new_image(img->mlx_ptr, img->width, img->height);
	if (!img->ptr)
		return (1);
	img->addr = mlx_get_data_addr(img->ptr, \
		&img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->addr)
		return (1);
	img->box_abs = mx_aabb(mx_pt(img->origin.x, img->origin.y), \
		mx_vec(img->width, img->height));
	img->box_rel = mx_aabb(mx_pt(0, 0), mx_vec(img->width, img->height));
	mx_log_img(MX_NAME, img);
	return (0);
}

#undef MX_NAME
#define MX_NAME "mx_create_xpm_img()"

int	mx_create_xpm_img(t_img *img, char *file)
{
	mx_log_img(MX_NAME, img);
	img->name = ft_strdup(file);
	if (!img->name)
		return (1);
	img->ptr = mlx_xpm_file_to_image(img->mlx_ptr, img->name, \
		&img->width, &img->height);
	if (!img->ptr)
		return (1);
	img->addr = mlx_get_data_addr(img->ptr, \
		&img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->addr)
		return (1);
	img->box_abs = mx_aabb(mx_pt(img->origin.x, img->origin.y), \
		mx_vec(img->width, img->height));
	img->box_rel = mx_aabb(mx_pt(0, 0), mx_vec(img->width, img->height));
	mx_log_img(MX_NAME, img);
	return (0);
}

#undef MX_NAME
#define MX_NAME "mx_destroy_img()"

void	mx_destroy_img(t_img *img)
{
	mx_log_img(MX_NAME, img);
	if (img == NULL)
		return ;
	if (img->ptr)
		mlx_destroy_image(img->mlx_ptr, img->ptr);
	if (img->name)
		free(img->name);
	ft_memset(img, 0, sizeof(t_img));
}

#undef MX_NAME
#define MX_NAME "mx_move_xy_img() box_abs"

void	mx_move_xy_img(t_img *img, int x, int y)
{
	img->box_abs = mx_aabb(mx_pt(x, y), img->box_abs.lenght);
	mx_log_aabb(MX_NAME, img->box_abs);
}

#undef MX_NAME
#define MX_NAME "mx_move_pt_img() box_abs"

void	mx_move_pt_img(t_img *img, t_2Dpt new_origin)
{
	img->box_abs = mx_aabb(new_origin, img->box_abs.lenght);
	mx_log_aabb(MX_NAME, img->box_abs);
}

#undef MX_NAME
#define MX_NAME "mx_draw_img()"

void	mx_draw_img(t_img *img)
{
	img->box_abs.origin = img->origin;
	mx_log_img(MX_NAME, img);
	if (false == mx_aabb_in_aabb(img->box_abs, img->win->box))
	{
		mx_log_win(MX_NAME, img->win);
		mx_log_img(MX_NAME, img);
		c_red();
		mx_log_msg("ERROR image outside window");
		c_reset();
		return ;
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win->ptr, img->ptr, \
		img->box_abs.origin.x, img->box_abs.origin.y);
}

#undef MX_NAME
#define MX_NAME "mx_fill_img()"

void	mx_fill_img(t_img *img, t_uint hexcolor)
{
	mx_log_img(MX_NAME, img);
	mx_fill_aabb(img, img->box_rel, hexcolor);
}
