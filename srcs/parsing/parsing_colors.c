/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:23:14 by edidier           #+#    #+#             */
/*   Updated: 2025/11/21 16:31:43 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	missing_space_error(char identifier)
{
	if (identifier == 'F')
		return (print_error("Missing space after floor identifier"));
	return (print_error("Missing space after ceiling identifier"));
}

int	parse_color_line(char *line, char identifier, int *target_color)
{
	char	*values;

	if (line[1] == '\0' || !ft_isspace((unsigned char)line[1]))
		return (missing_space_error(identifier));
	values = skip_spaces(line + 1);
	if (*values == '\0')
	{
		if (identifier == 'F')
			return (print_error("Missing floor color values"));
		return (print_error("Missing ceiling color values"));
	}
	return (parse_rgb_triplet(values, target_color));
}

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
