/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 19:22:33 by jinbekim          #+#    #+#             */
/*   Updated: 2021/01/05 20:16:10 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		eof_return(int readsize, char **backup, char **line)
{
	if (!backup)
	{
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

	if (fd < 0 || fd >= OPEN_MAX || !line || BUFFER_SIZE <= 0)
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
