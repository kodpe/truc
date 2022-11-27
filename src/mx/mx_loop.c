/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 20:59:58 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/27 05:24:21 by sloquet          ###   ########.fr       */
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

void	mx_log_loop_time(t_loop *loop)
{
	if (!MX_VERBOSE_LOOP)
		return ;
	fprintf(stderr, "==========================================\n");
	fprintf(stderr, "active                 [%i]\n", loop->active);
	fprintf(stderr, "loop_id                [%i]\n", loop->loop_id);
	fprintf(stderr, "last_loop_id           [%i]\n", loop->last_loop_id);
	if (loop->time_origin == 0)
		fprintf(stderr, "\033[1;31mTIME_ORIGIN\033[0m         ms [%lli]\n", loop->time_origin);
	else
		fprintf(stderr, "time_origin         ms [%lli]\n", loop->time_origin);
	fprintf(stderr, "time_elapsed        ms [%lli]  s [%lli]\n", loop->time_elapsed, loop->time_elapsed / 1000);
	fprintf(stderr, "timeout             ms [%lli]\n", loop->timeout);
	fprintf(stderr, "last_frame_duration ms [%lli]\n", loop->last_frame_duration);
	fprintf(stderr, "fps                fps [%i]\n", loop->fps);
	fprintf(stderr, "real_fps           fps [%.2f]\n", loop->real_fps);
	fprintf(stderr, "usleep_duration   usec [%i]\n", loop->usleep_duration);
	fprintf(stderr, "------------------------------------------\n");
}

// return (0) if loop init or 1
int	mx_time_loop(t_loop *loop, int fps, int sec_timeout)
{
	t_time	t;

	loop->fps = fps;
	t = mx_time_ms();
	loop->last_frame_duration = t - loop->time_origin - loop->time_elapsed;
	loop->real_fps = 1000.0 / (float)loop->last_frame_duration;
	if (loop->real_fps < loop->fps)
		loop->usleep_duration -= 100;
	if (loop->real_fps > loop->fps)
		loop->usleep_duration += 100;
	loop->time_elapsed = t - loop->time_origin;
	if (loop->time_origin == 0)
	{
		loop->usleep_duration = 1000000 / loop->fps;
		loop->time_elapsed = 0;
		loop->timeout = sec_timeout * 1000;
		mx_log_loop_time(loop);
		loop->time_origin = t;
		return (0);
	}
	mx_log_loop_time(loop);
	if (loop->timeout > 0 && loop->time_elapsed > loop->timeout)
		abort(); // TODO handle loop timeout if timeout > 0
	if (loop->fps < 1 || loop->fps > 1000)
		abort(); // TODO handle error invalid fps nb
	usleep(loop->usleep_duration);
	return (1);
}
