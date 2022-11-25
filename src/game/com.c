/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:52:34 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/25 13:31:19 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


char	*get_username(void)
{
	char	*username;

	username = ft_strdup(getenv("USER"));
	assert(username);
	return (username);
}

char	*get_username_code(void)
{
	char	*username_code;
	char	*num;

	num = ft_itoa(rand() % 90 + 10 + (rand() % 90 + 10) * 1000);
	username_code = ft_strjointri(getenv("USER"), "_", num);
	free(num);
	assert(username_code);
	return (username_code);
}

char	*set_username_code(char *name)
{
	char	*username_code;
	char	*num;

	num = ft_itoa(rand() % 90 + 10 + (rand() % 90 + 10) * 1000);
	username_code = ft_strjointri(name, "_", num);
	free(num);
	assert(username_code);
	return (username_code);
}

void	create_comfile(char *comfile_path)
{
	char	*cwd; 
	int		fd;
	
	assert(comfile_path);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		abort();
	if (-1 == chdir(PATH_COMDIR))
		abort();
	fd = open(comfile_path, O_CREAT | O_RDONLY | O_TRUNC, 0666);
	if (fd == -1)
		abort();
	close(fd);
	if (-1 == chdir(cwd))
		abort();
	free(cwd);
}

char	*get_user_photo(char *username)
{
	int		year;
	char	*num;
	char	*photo_name;
	char	*path;

	assert(username);
	assert(PATH_PHOTO);
	photo_name = ft_strjointri("/", username, ".JPG");
	if (!photo_name)
		abort();

	path = NULL;
	year = 2013;
	while (year < 2050)
	{
		num = ft_itoa(year);
		if (!num)
			abort();

		free(path);
		path = ft_strjointri(PATH_PHOTO, num, photo_name);
		free(num);
		if (!path)
			abort();
		if (0 == access(path, R_OK))
			break ;
		year++;
	}
	free(photo_name);
	if (year == 2050)
	{
		printf("\033[31munfound: [%s]\033[0m\n", path);
		free(path);
		return (NULL);

	}
	printf("\033[32mfound:       [%s]\033[0m\n", path);
	return (path);
}

int	resize_img(char *src_path, char *dest_path, t_2Dvec size_max)
{
	char	*cmd;
	char	*first_arg;
	char	*resize;
	char	*size;
	char	*size_x;
	char	*size_y;

	size_x = ft_itoa(size_max.x);
	size_y = ft_itoa(size_max.y);
	if (!size_x || !size_y)
		abort();
	size = ft_strjointri(size_x, "x", size_y);
	free(size_x);
	free(size_y);
	if (!size)
		abort();
	resize = ft_strjointri(" -resize ", size, " ");
	free(size);
	if (!resize)
		abort();
	first_arg = ft_strjointri(PATH_MAGICK, " ", src_path);
	if (!first_arg)
		abort();
	cmd = ft_strjointri(first_arg, resize, dest_path);
	free(first_arg);
	free(resize);
	printf("resize_img:system:cmd: [%s]\n", cmd);
	if (system(cmd))
	{
		printf("\033[31mKO\033[0m\n");
		free(cmd);
		return (-1);
	}
	printf("\033[32mOK\033[0m\n");
	free(cmd);
	return (0);
}

char	*get_42position(void)
{
	FILE	*fp;
	int		i;
	char	str[10];

	fp = popen("uname -n", "r");
	if (fp == NULL)
		return (ft_strdup("unknown position"));
	if (NULL == fgets(str, 10, fp))
	{
		pclose(fp);
		return (ft_strdup("unknown position"));
	}
	str[9] = '\0';
	pclose(fp);
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			break ;
		i++;
	}
	str[i] = '\0';
	return (ft_strdup(str));
}
