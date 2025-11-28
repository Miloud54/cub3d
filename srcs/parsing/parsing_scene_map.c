/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 11:10:09 by edidier           #+#    #+#             */
/*   Updated: 2025/11/28 15:03:35 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_valid_map_char(char c)
{
	if (c == ' ' || c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (BONUS && (c == 'D' || c == 'd' || c == 'M'))
		return (1);
	return (0);
}

int	looks_like_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\r')
	{
		if (!is_valid_map_char(line[i]))
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
