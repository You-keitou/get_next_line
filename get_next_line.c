/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyang   < jinyang@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 01:30:33 by jinyang           #+#    #+#             */
/*   Updated: 2022/08/01 08:51:42 by jinyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*split_ret_front(t_save *save)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = (char *)malloc(sizeof(char) * (save->cl_ptr - save->cur + 2));
	if (!ret)
		return (NULL);
	while (save->cur <= save->cl_ptr)
		ret[i++] = *(save->cur++);
	ret[i] = '\0';
	return (ret);
}

static void	marge_line(t_save *save, char *buffer)
{
	char	*tmp;

	if (*buffer != '\0')
	{
		if (save->content)
		{
			tmp = save->content;
			save->content = ft_strjoin(save->cur, buffer);
			free(tmp);
		}
		else
			save->content = ft_strdup(buffer);
		save->cur = save->content;
	}
}

static void	read_till_lf(int fd, char *buffer, t_save *save)
{
	ssize_t	readbyte;

	readbyte = read(fd, buffer, BUFFER_SIZE);
	if (readbyte < 0)
	{
		if (save->content)
			free(save->content);
		save->content = NULL;
		save->cl_ptr = NULL;
		save->cur = NULL;
		save->flag = true;
		return ;
	}
	buffer[readbyte] = '\0';
	if (readbyte < BUFFER_SIZE && fd != 1)
		save->flag = true;
	marge_line(save, buffer);
}

static char	*make_line(t_save *save)
{
	char	*ret;

	ret = NULL;
	if (save->content == NULL)
		return (NULL);
	if (save->cl_ptr)
		ret = split_ret_front(save);
	else if (save->flag)
	{
		ret = save->content;
		save->content = NULL;
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static t_save	save = {NULL, NULL, NULL, false};
	char			*ret;
	char			buffer[BUFFER_SIZE + 1];

	ret = NULL;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (save.content)
		{
			if (*save.cur == '\0' && save.flag)
			{
				free(save.content);
				break ;
			}
			save.cl_ptr = ft_strchr(save.cur, '\n');
			if (save.cl_ptr)
				ret = make_line(&save);
			else if (!save.flag)
				read_till_lf(fd, buffer, &save);
		}
		else if (!save.flag)
			read_till_lf(fd, buffer, &save);
		if (ret)
			break ;
		if (save.content == NULL && save.flag == true)
			break ;
	}
	return (ret);
}
