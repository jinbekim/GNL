/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 19:22:33 by jinbekim          #+#    #+#             */
/*   Updated: 2021/01/06 00:37:55 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		eof_return(int readsize, char **backup, char **line)
{
	if (!(*backup))
	{
		if (readsize == -1)
			return (readsize);
		else
			*line = ft_strdup("");
	}
	else
	{
		*line = *backup;
		*backup = NULL;
	}
	return (readsize);
}

int		get_next_line(int fd, char **line)
{
	int				readsize;
	char			buff[BUFFER_SIZE + 1];
	static char		*backup[OPEN_MAX] = {0, };

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || !line)
		return (-1);
	while (has_newline(backup[fd]) == -1)
	{
		if ((readsize = read(fd, buff, BUFFER_SIZE)) <= 0)
			return (eof_return(readsize, &backup[fd], line));
		buff[readsize] = '\0';
		if (!backup[fd])
			backup[fd] = ft_strdup(buff);
		else
			backup[fd] = ft_strjoin_free(backup[fd], buff);
	}
	*line = backup[fd];
	cut_with_newline(&backup[fd]);
	return (1);
}
