/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:20:24 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/21 12:18:12 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
