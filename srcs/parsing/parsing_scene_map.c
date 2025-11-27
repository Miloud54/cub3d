/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 11:10:09 by edidier           #+#    #+#             */
/*   Updated: 2025/11/21 16:24:47 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	looks_like_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\r')
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
#if BONUS
			&& line[i] != 'D' && line[i] != 'd'
#endif
			)
			return (0);
		i++;
	}
	return (i > 0);
}

int	process_map_line(char *line, t_scene *scene)
{
	if (!append_map_line(&scene->map_lines, line, &scene->map_width))
		return (0);
	scene->map_height++;
	return (1);
}
