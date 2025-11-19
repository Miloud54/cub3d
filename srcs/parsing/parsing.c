/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:41:29 by edidier           #+#    #+#             */
/*   Updated: 2025/11/19 14:46:51 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	open_map_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

static int	read_map_lines(int fd, t_list **lines)
{
	char	*tmp;
	int		nb_lines;
	char	*line;

	tmp = NULL;
	nb_lines = 0;
	line = get_next_line(fd, &tmp);
	while (line)
	{
		if (line[0] != '\n' && line[0] != '\0')
		{
			ft_lstadd_back(lines, ft_lstnew(line));
			nb_lines++;
		}
		else
			free(line);
		line = get_next_line(fd, &tmp);
	}
	free_gnl_tmp(&tmp);
	return (nb_lines);
}

static char	**list_to_array(t_list *lines, int nb_lines)
{
	char	**map;
	int		i;
	t_list	*tmp;

	map = malloc(sizeof(char *) * (nb_lines + 1));
	if (!map)
	{
		ft_lstclear(&lines, free);
		return (NULL);
	}
	i = 0;
	while (lines)
	{
		map[i++] = lines->content;
		tmp = lines;
		lines = lines->next;
		free(tmp);
	}
	map[i] = NULL;
	return (map);
}

char	**load_map(const char *filename)
{
	t_list	*lines;
	int		nb_lines;
	char	**map;
	int		fd;

	fd = open_map_file(filename);
	if (fd < 0)
	{
		print_error("Error opening map file.");
		return (NULL);
	}
	lines = NULL;
	nb_lines = read_map_lines(fd, &lines);
	close(fd);
	if (nb_lines == 0)
	{
		print_error("Empty or invalid map file.");
		return (NULL);
	}
	map = list_to_array(lines, nb_lines);
	if (!map)
	{
		ft_lstclear(&lines, free);
		return (NULL);
	}
	return (map);
}
