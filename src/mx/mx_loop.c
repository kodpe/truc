/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 20:59:58 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/25 21:05:38 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mx.h"

void	mx_wait_fps(int frame_per_second)
{
	if (frame_per_second < 1 || frame_per_second > 1000)
		abort();
	usleep(1000000 / frame_per_second);
}
