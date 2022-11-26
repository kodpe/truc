/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 20:59:58 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/26 16:25:19 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

void	mx_wait_fps(int frame_per_second)
{
	if (frame_per_second < 1 || frame_per_second > 1000)
		abort();
	usleep(1000000 / frame_per_second);
}

t_time	mx_sc_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

t_time	mx_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	mx_loop_time(t_loop *loop)
{
	t_time	t;

	t = mx_time_ms();
	loop->time_elapsed += t - loop->time_origin;
	if (loop->time_origin == 0)
	{
		loop->time_origin = t;
		loop->time_elapsed = 0;
	}
	if (loop->timeout > 0 && loop->time_elapsed > loop->timeout)
		abort(); // TODO handle loop timeout if timeout > 0
	if (loop->fps < 1 || loop->fps > 1000)
		abort(); // TODO handle error invalid fps nb
	usleep(1000000 / loop->fps);
}
