/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfauvell <cfauvell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:55:45 by cfauvell          #+#    #+#             */
/*   Updated: 2018/11/27 07:06:10 by cfauvell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*security(int fd, char *str, char **line)
{
	if (fd < 0 || line == NULL)
		return (NULL);
	if (!str)
	{
		if (!(str = ft_strnew(0)))
			return (NULL);
	}
	return (str);
}

char	*readline(char *str, int fd)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;
	char	*tmp;

	ret = 1;
	while (!(ft_strchr(str, '\n')) && ret > 0)
	{
		ret = read(fd, buff, BUFF_SIZE);
		if (ret > 0)
		{
			//tmp = str ? str : NULL;
			buff[ret] = '\0';
			if (!(str = ft_strjoin(str, buff)))
				return (NULL);
			//if (tmp)
				//ft_strdel(&tmp);
		}
	}
	if (ret == -1)
	{
		ft_strdel(&str);
		return (NULL);
	}
	return (str);
}

int		get_next_line(int const fd, char **line)
{
	static char	*str;
	int			lcount;
	char		*tmp;

	if (!(str = security(fd, str, line)))
		return (-1);
	if (!(str = readline(str, fd)))
		return (-1);
	lcount = 0;
	if (str[lcount])
	{
		lcount = ft_strclen(str, '\n');
		if (lcount == 0)
			*line = ft_strdup("");
		else
			*line = ft_strndup(str, lcount);
		tmp = str;
		str = ft_strdup(&str[lcount + 1]);
		free(tmp);
		return (1);
	}
	else
		*line = ft_strdup("");
	return (0);
}
