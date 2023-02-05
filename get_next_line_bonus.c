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

#include "get_next_line_bonus.h"

static char	*split_ret_front(t_save *save, char *new_line_ptr)
{
	char	*tmp;
	char	*line;
	ssize_t	len;
	ssize_t	i;

	len = new_line_ptr - save->content + 2;
	line = (char *)malloc(sizeof(char) * len);
	if (!line)
	{
		free(save->content);
		save->content = NULL;
		return (NULL);
	}
	i = -1;
	while (++i < len - 1)
		line[i] = *(save->content + i);
	line[i] = '\0';
	tmp = save->content;
	if (*(new_line_ptr + 1) != '\0')
		save->content = ft_strdup(new_line_ptr + 1);
	else
		save->content = NULL;
	free(tmp);
	return (line);
}

static char	*marge_line(t_save *save, char *buffer)
{
	char	*tmp;

	if (*buffer != '\0')
	{
		if (save->content)
		{
			tmp = save->content;
			save->content = ft_strjoin(tmp, buffer);
			free(tmp);
		}
		else
			save->content = ft_strdup(buffer);
	}
	return (save->content);
}

static void	read_till_lf(int fd, char *buffer, t_save *save)
{
	ssize_t	readbyte;

	if (!save->flag)
	{
		readbyte = read(fd, buffer, BUFFER_SIZE);
		if (readbyte < 0)
		{
			if (save->content)
				free(save->content);
			save->content = NULL;
			save->flag = true;
			return ;
		}
		buffer[readbyte] = '\0';
		if (readbyte < BUFFER_SIZE && fd != 1)
			save->flag = true;
		save->content = marge_line(save, buffer);
	}
}

static char	*make_line(t_save *save)
{
	char	*new_line_ptr;
	char	*ret;

	ret = NULL;
	if (save->content == NULL)
		return (NULL);
	new_line_ptr = ft_strchr(save->content, '\n');
	if (new_line_ptr)
		ret = split_ret_front(save, new_line_ptr);
	else if (save->flag)
	{
		ret = save->content;
		save->content = NULL;
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static t_save	save[MAX_FD_SIZE] = {{NULL, false}};
	char			*ret;
	char			buffer[BUFFER_SIZE + 1];

	if (fd < 0 || fd > MAX_FD_SIZE - 1 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (!save[fd].flag)
			read_till_lf(fd, buffer, &save[fd]);
		ret = make_line(&save[fd]);
		if (ret)
			break ;
		if (save[fd].content == NULL && save[fd].flag == true)
			break ;
	}
	return (ret);
}
