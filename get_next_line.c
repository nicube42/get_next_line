/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:07:38 by ndiamant          #+#    #+#             */
/*   Updated: 2023/01/10 14:39:13 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*test_empty(char **stack)
{
	if (!*stack)
		return (0);
	else if (!**stack)
		return (0);
	return (*stack);
}

char	*gnl_ret(char **stock)
{
	char	*line;
	char	*tmp;
	int		i;
	int		j;

	if (test_empty(stock) == 0)
	{
		free (*stock);
		*stock = 0;
		return (0);
	}
	if (!ft_strchr(*stock, '\n'))
	{
		line = ft_substr(*stock, 0, ft_strlen(*stock));
		free (*stock);
		*stock = 0;
		return (line);
	}
	i = ft_strlen(*stock);
	j = ft_strlen(ft_strchr(*stock, '\n'));
	line = ft_substr(*stock, 0, i - j + 1);
	tmp = *stock;
	*stock = ft_substr(ft_strchr(*stock, '\n'), 1, j - 1);
	free (tmp);
	return (line);
}

void	fill_buffer(char *buffer, char **stock, int fd, int char_count)
{
	char	*tmp;

	while (char_count > 0)
	{
		buffer[char_count] = '\0';
		if (!*stock)
			*stock = ft_substr(buffer, 0, char_count);
		else
		{
			tmp = *stock;
			*stock = ft_strjoin(*stock, buffer);
			free (tmp);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
		char_count = read(fd, buffer, BUFFER_SIZE);
		if (char_count == -1)
		{
			free (*stock);
			*stock = 0;
		}
	}
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*buffer;
	int			char_count;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
	{
		free (buffer);
		free (stock);
		stock = 0;
		return (0);
	}
	if (!stock || !ft_strchr(stock, '\n'))
	{
		char_count = read(fd, buffer, BUFFER_SIZE);
		if (char_count == -1)
		{
			free (stock);
		}
		fill_buffer(buffer, &stock, fd, char_count);
	}
	free (buffer);
	return (gnl_ret(&stock));
}
