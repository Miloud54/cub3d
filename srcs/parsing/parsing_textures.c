/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:32:54 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/19 16:16:16 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Extrait le chemin de texture d'une ligne
static char	*extract_texture_path(char *line)
{
	int		i;
	int		start;
	int		end;
	char	*path;

	// Passer l'identifiant (NO, SO, WE, EA)
	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	// Passer les espaces
	while (line[i] && ft_isspace(line[i]))
		i++;
	start = i;
	// Aller jusqu'à la fin du chemin
	while (line[i] && line[i] != '\n' && line[i] != '\r')
		i++;
	end = i;
	// Enlever les espaces à la fin
	while (end > start && ft_isspace(line[end - 1]))
		end--;
	if (end <= start)
		return (NULL);
	path = ft_substr(line, start, end - start);
	return (path);
}

// Parse une ligne de texture et l'assigne à la bonne direction
static int	parse_texture_line(char *line, t_textures *textures)
{
	char	*path;

	path = extract_texture_path(line);
	if (!path)
		return (print_error("Invalid texture path format"));
	
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (textures->north != NULL)
			return (free(path), print_error("Duplicate NO texture"));
		textures->north = path;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (textures->south != NULL)
			return (free(path), print_error("Duplicate SO texture"));
		textures->south = path;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (textures->west != NULL)
			return (free(path), print_error("Duplicate WE texture"));
		textures->west = path;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (textures->east != NULL)
			return (free(path), print_error("Duplicate EA texture"));
		textures->east = path;
	}
	else
		return (free(path), print_error("Unknown texture identifier"));
	return (1);
}

// Parse les textures depuis un fichier .cub
int	parse_textures(const char *filename, t_textures *textures)
{
	int		fd;
	char	*line;
	char	*tmp;
	int		texture_count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Cannot open file"));
	
	tmp = NULL;
	texture_count = 0;
	while ((line = get_next_line(fd, &tmp)) != NULL)
	{
		// Ignorer les lignes vides
		if (line[0] == '\n' || line[0] == '\r')
		{
			free(line);
			break; // Première ligne vide = fin des textures
		}
		// Ignorer les commentaires ou lignes qui ne sont pas des textures
		if (line[0] != 'N' && line[0] != 'S' && line[0] != 'W' && line[0] != 'E')
		{
			free(line);
			continue;
		}
		if (!parse_texture_line(line, textures))
		{
			free(line);
			free_gnl_tmp(&tmp);
			close(fd);
			return (0);
		}
		texture_count++;
		free(line);
		if (texture_count >= 4)
			break;
	}
	free_gnl_tmp(&tmp);
	close(fd);
	return (1);
}

// Valide que toutes les textures sont présentes, différentes et existent
int	validate_textures(t_textures *textures)
{
	// Vérifier que toutes les textures sont présentes
	if (!textures->north || !textures->south || !textures->west || !textures->east)
		return (print_error("Missing texture(s): need NO, SO, WE, EA"));
	// Vérifier que toutes les textures sont différentes
	if (ft_strcmp(textures->north, textures->south) == 0 ||
		ft_strcmp(textures->north, textures->west) == 0 ||
		ft_strcmp(textures->north, textures->east) == 0 ||
		ft_strcmp(textures->south, textures->west) == 0 ||
		ft_strcmp(textures->south, textures->east) == 0 ||
		ft_strcmp(textures->west, textures->east) == 0)
		return (print_error("All textures must be different"));
	// Vérifier que tous les fichiers existent
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
