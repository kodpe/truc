/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:15:53 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/11 19:35:27 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

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
#define MX_NAME "mx_open_xpm_img()"

int	mx_open_xpm_img(void *mlx_ptr, t_img *img, char *file)
{
	ft_memset(img, 0, sizeof(t_img));
	img->name = ft_strdup(file);
	if (!img->name)
		return (1);
	img->ptr = mlx_xpm_file_to_image(mlx_ptr, file, &img->width, &img->height);
	if (!img->ptr)
		return (1);
	img->addr = mlx_get_data_addr(img->ptr, \
		&img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->addr)
		return (1);
	img->box = mx_aabb(mx_pt(0, 0), mx_vec(img->width, img->height));
	img->mlx_ptr = mlx_ptr;
	mx_log_img(MX_NAME, img);
	return (0);
}

#undef MX_NAME
#define MX_NAME "mx_new_img()"

int	mx_new_img(void *mlx_ptr, t_img *img, int width, int height)
{
	ft_memset(img, 0, sizeof(t_img));
	img->width = width;
	img->height = height;
	if (width < 1 || height < 1)
		return (1);
	img->ptr = mlx_new_image(mlx_ptr, img->width, img->height);
	if (!img->ptr)
		return (1);
	img->addr = mlx_get_data_addr(img->ptr, \
		&img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->addr)
		return (1);
	img->box = mx_aabb(mx_pt(0, 0), mx_vec(img->width, img->height));
	img->mlx_ptr = mlx_ptr;
	mx_log_img(MX_NAME, img);
	return (0);
}

#undef MX_NAME
#define MX_NAME "mx_reset_img()"

int	mx_reset_img(t_img *img)
{
	t_2Dvec	size;
	void	*mlx_ptr;

	mx_log_img(MX_NAME, img);
	size = mx_vec(img->width, img->height);
	mlx_ptr = img->mlx_ptr;
	mx_destroy_img(img);
	if (mx_new_img(mlx_ptr, img, size.x, size.y))
		return (1);
	mx_log_img(MX_NAME, img);
	return (0);
}

#undef MX_NAME
#define MX_NAME "mx_draw_img()"

void	mx_draw_img(void *mlx_ptr, t_win *win, t_img *img)
{
	mx_log_img(MX_NAME, img);
	if (false == mx_aabb_in_aabb(img->box, win->box))
	{
		mx_log_win("mx_draw_image() err", win);
		mx_log_img("mx_draw_image() err", img);
		abort();
	}
	mlx_put_image_to_window(mlx_ptr, win->ptr, img->ptr, \
		img->box.origin.x, img->box.origin.y);
}

#undef MX_NAME
#define MX_NAME "mx_fill_img()"

void	mx_fill_img(t_img *img, int hexcolor)
{
	mx_log_img(MX_NAME, img);
	mx_fill_aabb(img, img->box, hexcolor);
}
