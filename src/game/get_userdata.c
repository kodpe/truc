/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_userdata.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:33:40 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 15:57:04 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


t_userdata	_default_userdata(void)
{
	t_userdata	ud;

	ft_memset(&ud, 0, sizeof(t_userdata));
	ud.name = ft_strdup("no_name");
	ud.personal_user_photo = ft_strdup("no_photo_path");
	return (ud);
}


t_userdata	get_userdata(char *name)
{
	char	*path;
	int		fd;
	char	*line;
	char	**sp;
	t_userdata	ud;

	assert(name);
	path = ft_strjointri(PATH_USERDATA, name, ".ud");
	fd = open(path, O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		abort();
	free(path);
	line = get_next_line(fd);
	ft_close_gnl(fd);
	close(fd);
	if (!line)
		return (_default_userdata());
	sp = ft_split(line);
	if (!sp)
		abort();


	ft_arfree(sp);
	free(line);

}
