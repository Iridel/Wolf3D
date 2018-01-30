/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 02:17:21 by dhill             #+#    #+#             */
/*   Updated: 2018/01/29 16:18:24 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

char	**parse_map(int fd, int width, int height)
{
	int		chk;
	int		h;
	char	*line;
	char	**data;
	char	*ones;

	h = 0;
	line = NULL;
	data = (char **)ft_memalloc(sizeof(char *) * (height + 1));
	ones = ft_strnew(width);
	ft_memset(ones, '1', width);
	while ((chk = get_next_line(fd, &line)) > 0)
	{
		((int)ft_strlen(line) != width) ?
			ft_error("File width doesn't match") : 0;
		if (line[0] != '1' || line[width - 1] != '1')
			ft_error("Map is not sealed.");
		data[h] = ft_strdup(line);
		h++;
		ft_strdel(&line);
	}
	if (!ft_strequ(data[0], ones) || !ft_strequ(data[height - 1], ones))
		ft_error("Map is not sealed.");
	ft_strdel(&ones);
	return (data);
}

char	**parse(char *file)
{
	int		fd;

	(fd = open(file, O_RDONLY)) <= 0 ? ft_error("Cannot open file.") : 0;
	if (ft_strstr(file, ".map") == 0)
		ft_error("File selected is not .map file");
	if (ft_strequ(file, "./maps/start.map") == 1)
		return (parse_map(fd, 17, 15));
	if (ft_strequ(file, "./maps/side.map") == 1)
		return (parse_map(fd, 19, 31));
	if (ft_strequ(file, "./maps/other.map") == 1)
		return (parse_map(fd, 55, 35));
	if (ft_strequ(file, "./maps/large.map") == 1)
		return (parse_map(fd, 39, 55));
	if (ft_strequ(file, "./maps/largest.map") == 1)
		return (parse_map(fd, 55, 55));
	if (ft_strequ(file, "./maps/loop.map") == 1)
		return (parse_map(fd, 15, 15));
	ft_error("Nothing was parsed.");
	return (NULL);
}
