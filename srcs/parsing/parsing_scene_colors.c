/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_colors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 11:09:15 by edidier           #+#    #+#             */
/*   Updated: 2025/11/21 12:18:06 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	handle_color_line(char *trimmed, t_scene *scene)
{
	if (*trimmed == 'F' && ft_isspace((unsigned char)trimmed[1]))
	{
		if (scene->floor_found)
			return (print_error("Duplicate floor color definition"));
		if (!parse_color_line(trimmed, 'F', &scene->game->floor_color))
			return (0);
		scene->floor_found = 1;
		return (1);
	}
	if (*trimmed == 'C' && ft_isspace((unsigned char)trimmed[1]))
	{
		if (scene->ceiling_found)
			return (print_error("Duplicate ceiling color definition"));
		if (!parse_color_line(trimmed, 'C', &scene->game->ceiling_color))
			return (0);
		scene->ceiling_found = 1;
		return (1);
	}
	return (-1);
}
