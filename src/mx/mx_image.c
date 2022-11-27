/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:15:53 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/25 23:05:43by sloquet          ###   ########.fr       */
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
	img->box_rel = mx_aabb(mx_pt(0, 0), mx_vec(img->width - 1, img->height - 1));
	mx_log_img(MX_NAME, img);
	return (0);
}

#undef MX_NAME
#define MX_NAME "mx_create_xpm_img()"

int	mx_create_xpm_img(t_img *img, char *file)
{
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
	img->box_rel = mx_aabb(mx_pt(0, 0), mx_vec(img->width - 1, img->height - 1));
	mx_log_img(MX_NAME, img);
	return (0);
}

#undef MX_NAME
#define MX_NAME "mx_destroy_img()"

void	mx_destroy_img(t_img *img)
{
	if (img == NULL)
		return ;
	mx_log_img(MX_NAME, img);
	if (img->ptr)
		mlx_destroy_image(img->mlx_ptr, img->ptr);
	if (img->name)
		free(img->name);
	ft_memset(img, 0, sizeof(t_img));
}

#undef MX_NAME
#define MX_NAME "mx_move_abs_xy_img() box_abs"

void	mx_move_abs_xy_img(t_img *img, int x, int y)
{
	t_aabb	next_imgbox;

	next_imgbox = mx_aabb(mx_pt(x, y), img->box_abs.lenght);
	mx_fill_not2aabb(img, img->box_abs, next_imgbox, BLACK);
	mx_draw_img(img);
	img->origin = mx_pt(x, y);
	img->box_abs.origin = mx_pt(x, y);
	mx_log_aabb(MX_NAME, img->box_abs);
	if (mx_reset_img(img))
		abort();
}

void	mx_move_rel_xy_img(t_img *img, int x, int y)
{
	mx_move_abs_xy_img(img, img->origin.x + x, img->origin.y + y);
}

void	mx_move_abs_pt_img(t_img *img, t_2Dpt new_origin)
{
	mx_move_abs_xy_img(img, new_origin.x, new_origin.y);
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

void	mx_fill_img_bg(t_img *front, t_img *backg)
{
	if (!mx_coll_aabb(front->box_abs, backg->box_abs))
		return ;
	int		x;
	int		y;
	t_2Dpt	ab;
	t_2Dpt	bg;
	t_uint	bg_color;

	y = 0;
	while (y < front->height)
	{
		x = 0;
		while (x < front->width)
		{
			ab = mx_pt(front->origin.x + x, front->origin.y + y);
			if (mx_coll_pt_aabb(ab, backg->box_abs))
			{
				if (mx_get_pixel_color(front, x, y) == 0xFF000000)
				{
					bg = mx_pt(ab.x - backg->origin.x, ab.y - backg->origin.y);
					bg_color = mx_get_pixel_color(backg, bg.x, bg.y);
					mx_draw_pixel(front, x, y, bg_color);
				}
			}
			x++;
		}
		y++;
	}
}

#undef MX_NAME
#define MX_NAME "mx_reset_img()"

int	mx_reset_img(t_img *img)
{
	if (img == NULL || img->ptr == NULL)
		return (1);
	mlx_destroy_image(img->mlx_ptr, img->ptr);
	if (ft_is_extension(img->name, ".xpm"))
		img->ptr = mlx_xpm_file_to_image(img->mlx_ptr, \
				img->name, &img->width, &img->height);
	else
		img->ptr = mlx_new_image(img->mlx_ptr, img->width, img->height);
	if (!img->ptr)
		return (1);
	img->addr = mlx_get_data_addr(img->ptr, \
		&img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->addr)
		return (1);
	img->box_abs = mx_aabb(mx_pt(img->origin.x, img->origin.y), \
		mx_vec(img->width, img->height));
	img->box_rel = mx_aabb(mx_pt(0, 0), mx_vec(img->width - 1, img->height - 1));
	mx_log_img(MX_NAME, img);
	return (0);
}

void	mx_draw_box_img(t_img *img, t_uint hexcolor)
{
	mx_draw_aabb(img, img->box_rel, hexcolor);
}

void	mx_grid_img(t_img *img, t_2Dvec nb_tiles, t_uint hexcolor)
{
	mx_grid_aabb(img, img->box_rel, nb_tiles, hexcolor);
}

void	mx_putstr_img(t_img *img, t_2Dpt origin, char *str, t_uint hexcolor)
{
	if (!str)
		return ;
	mlx_string_put(img->mlx_ptr, img->win->ptr, \
					origin.x, origin.y, \
					hexcolor, str);
}

void	mx_putstr_cen_img(t_img *img, char *str, t_uint hexcolor)
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
	mlx_string_put(img->mlx_ptr, img->win->ptr, \
					img->origin.x + img->width / 2 - offset / 2, \
					img->origin.y + img->height / 2 - 12, \
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
	mx_putstr_cen_img(img, str, hexcolor);
	free(str);
}

/*
--------------------------------------------------
| LT                    CT                    RT |
|                                                |
|                                                |
| LC                    CC                    RC |
|                                                |
|                                                |
| LB                    CB                    RB |
--------------------------------------------------
*/
t_2Dpt	mx_getpt_img(t_img *img, char *mode)
{
	t_2Dpt	pt;

	if (ft_strlen(mode) != 4)
		abort();
	if (mode[0] != 'A' && mode[0] != 'R')
		abort();
	if (mode[1] != '.')
		abort();
	if (mode[2] != 'L' && mode[2] != 'C' && mode[2] != 'R')
		abort();
	if (mode[3] != 'T' && mode[3] != 'C' && mode[3] != 'B')
		abort();
	if (mode[0] == 'A')
		pt = mx_pt(0, 0);
	if (mode[0] == 'R')
		pt = img->origin;
	if (mode[2] == 'C')
		pt.x += img->width / 2;
	if (mode[2] == 'R')
		pt.x += img->width;
	if (mode[3] == 'C')
		pt.y += img->height / 2;
	if (mode[3] == 'B')
		pt.y += img->height;
	return (pt);
}
