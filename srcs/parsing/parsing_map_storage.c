/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_storage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:12:12 by emiliedidie       #+#    #+#             */
/*   Updated: 2025/11/28 13:56:09 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	validate_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\r')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
#if BONUS
			&& line[i] != 'D' && line[i] != 'd' && line[i] != ENEMY_SPAWN_CHAR
#endif
		)
			return (0);
		i++;
	}
	return (i > 0);
}

char	*dup_map_line(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		len--;
	return (ft_substr(line, 0, len));
}

int	append_map_line(t_list **lines, char *line, int *max_width)
{
	char	*dup;
	t_list	*node;
	size_t	len;

	if (!validate_map_line(line))
		return (print_error("Invalid character in map"));
	dup = dup_map_line(line);
	if (!dup)
		return (print_error("Failed to duplicate map line"));
	node = ft_lstnew(dup);
	if (!node)
	{
		free(dup);
		return (print_error("Failed to allocate map line"));
	}
	ft_lstadd_back(lines, node);
	len = ft_strlen(dup);
	if ((int)len > *max_width)
		*max_width = (int)len;
	return (1);
}

char	**list_to_array(t_list **lines, int height)
{
	char	**map;
	int		i;
	t_list	*tmp;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
	{
		ft_lstclear(lines, free);
		return (NULL);
	}
	i = 0;
	while (*lines)
	{
		map[i++] = (*lines)->content;
		tmp = *lines;
		*lines = (*lines)->next;
		free(tmp);
	}
	map[i] = NULL;
	return (map);
}
