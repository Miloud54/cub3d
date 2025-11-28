/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:20:24 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/28 13:56:20 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	store_texture_path(char **target, char *content,
		char *duplicate_msg, char *missing_msg)
{
	size_t	len;
	char	*path;

	if (*target != NULL)
		return (print_error(duplicate_msg));
	while (*content && ft_isspace((unsigned char)*content))
		content++;
	len = ft_strlen(content);
	while (len > 0 && ft_isspace((unsigned char)content[len - 1]))
		len--;
	if (len == 0)
		return (print_error(missing_msg));
	path = ft_substr(content, 0, len);
	if (!path)
		return (print_error("Failed to allocate texture path"));
	if (!is_valid_extension_xpm(path))
	{
		free(path);
		return (0);
	}
	*target = path;
	return (1);
}

int	handle_texture_line(char *trimmed, t_game *game)
{
	if (ft_strncmp(trimmed, "NO", 2) == 0
		&& ft_isspace((unsigned char)trimmed[2]))
		return (store_texture_path(&game->textures.north, trimmed + 2,
				"Duplicate north texture definition",
				"Missing north texture path"));
	if (ft_strncmp(trimmed, "SO", 2) == 0
		&& ft_isspace((unsigned char)trimmed[2]))
		return (store_texture_path(&game->textures.south, trimmed + 2,
				"Duplicate south texture definition",
				"Missing south texture path"));
	if (ft_strncmp(trimmed, "WE", 2) == 0
		&& ft_isspace((unsigned char)trimmed[2]))
		return (store_texture_path(&game->textures.west, trimmed + 2,
				"Duplicate west texture definition",
				"Missing west texture path"));
	if (ft_strncmp(trimmed, "EA", 2) == 0
		&& ft_isspace((unsigned char)trimmed[2]))
		return (store_texture_path(&game->textures.east, trimmed + 2,
				"Duplicate east texture definition",
				"Missing east texture path"));
	return (-1);
}

int	validate_textures(t_textures *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (print_error("Missing texture(s): need NO, SO, WE, EA"));
	if (ft_strcmp(textures->north, textures->south) == 0
		|| ft_strcmp(textures->north, textures->west) == 0
		|| ft_strcmp(textures->north, textures->east) == 0
		|| ft_strcmp(textures->south, textures->west) == 0
		|| ft_strcmp(textures->south, textures->east) == 0
		|| ft_strcmp(textures->west, textures->east) == 0)
		return (print_error("All textures must be different"));
	if (!is_valid_extension_xpm(textures->north)
		|| !is_valid_extension_xpm(textures->south)
		|| !is_valid_extension_xpm(textures->west)
		|| !is_valid_extension_xpm(textures->east))
		return (0);
	if (!file_exists(textures->north))
		return (print_error("North texture file not found"));
	if (!file_exists(textures->south))
		return (print_error("South texture file not found"));
	if (!file_exists(textures->west))
		return (print_error("West texture file not found"));
	if (!file_exists(textures->east))
		return (print_error("East texture file not found"));
	return (1);
}
