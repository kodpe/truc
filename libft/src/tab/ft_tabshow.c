/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabshow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 07:32:03 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 14:53:25 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hsl_tab.h"

void	ft_tabshow(const int *tab, const int size, const char *name)
{
	int	i;

	ft_printf("ft_tabshow %s\n", name);
	i = 0;
	while (i < size)
	{
		ft_printf("%s[%d] = %d\n", name, i, tab[i]);
		i++;
	}
	ft_putnl();
}

void	ft_tabfshow(const float *tab, const int size, const char *name)
{
	int	i;

	ft_printf("ft_tabshow %s\n", name);
	i = 0;
	while (i < size)
	{
		printf("%s[%d] = [%f]\n", name, i, tab[i]);
		i++;
	}
	ft_putnl();
}
