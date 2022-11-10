/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_show.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:13:03 by sloquet           #+#    #+#             */
/*   Updated: 2022/01/29 15:18:37 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hsl_stack.h"

void	ft_stack_show(t_stack *s)
{
	int	i;

	i = s->top;
	while (i >= 0)
	{
		ft_printf("%d\n", s->t[i]);
		i--;
	}
}
