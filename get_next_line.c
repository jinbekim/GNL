/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 19:22:33 by jinbekim          #+#    #+#             */
/*   Updated: 2021/01/02 22:00:57 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		last_return(int readsize, char *backup, char **line)
{
	*line = backup;
	if (ft_strchr(backup, '\n'))
	{
		cut_with_newline(&backup);
		if (!backup)
			return (readsize);
		else if (readsize == 0)
			return (1);
		else
			return (-1);
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
	while (!ft_strchr(backup[fd], '\n'))
	{
		if ((readsize = read(fd, buff, BUFFER_SIZE)) <= 0)
			return (last_return(readsize, backup[fd], line));
		buff[readsize] = '\0';
		if (!backup[fd])
			backup[fd] = ft_strdup(buff);
		else
			backup[fd] = ft_strjoin_free(backup[fd], buff);
	}
	if (readsize = read(fd, buff, BUFFER_SIZE) <= 0)
		return (last_return(readsize, backup[fd], line));
	buff[readsize] = '\0';
	backup[fd] = ft_strjoin_free(backup[fd], buff);
	*line = backup[fd];
	cut_with_newline(&backup[fd]);
	return (1);
}
