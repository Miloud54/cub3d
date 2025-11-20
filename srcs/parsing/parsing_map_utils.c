/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedidier <emiliedidier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:22:41 by emiliedidie       #+#    #+#             */
/*   Updated: 2025/11/21 13:22:41 by emiliedidie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	has_identifier_suffix(char *line, size_t len)
{
	if (line[len] == '\0' || line[len] == '\n' || line[len] == '\r')
		return (1);
	return (ft_isspace(line[len]));
}

int	is_map_identifier(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 && has_identifier_suffix(line, 2))
		return (1);
	if (ft_strncmp(line, "SO", 2) == 0 && has_identifier_suffix(line, 2))
		return (1);
	if (ft_strncmp(line, "WE", 2) == 0 && has_identifier_suffix(line, 2))
		return (1);
	if (ft_strncmp(line, "EA", 2) == 0 && has_identifier_suffix(line, 2))
		return (1);
	if (line[0] == 'F' && (line[1] == '\0' || line[1] == '\n'
			|| line[1] == '\r' || ft_isspace(line[1])))
		return (1);
	if (line[0] == 'C' && (line[1] == '\0' || line[1] == '\n'
			|| line[1] == '\r' || ft_isspace(line[1])))
		return (1);
	return (0);
}
