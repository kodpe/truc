/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:21:59 by sloquet           #+#    #+#             */
/*   Updated: 2022/12/02 14:29:35 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hsl_file.h"

char	**ft_getfile(char *path)
{
	char	**data;
	int		fd;
	int		i;
	int		len;

	len = ft_filelen(path);
	data = (char **)malloc(sizeof(char *) * (len + 1));
	if (!data)
		return (NULL);
	data[len] = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("ft_gnln");
		return (NULL);
	}
	i = 0;
	while (1)
	{
		data[i] = get_next_line(fd);
		if (!data[i])
			break;
		i++;
	}
	close(fd);
	return (data);
}
