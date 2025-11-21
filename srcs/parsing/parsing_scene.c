/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 10:12:12 by edidier           #+#    #+#             */
/*   Updated: 2025/11/21 12:18:11 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	process_scene_line(char *line, t_scene *scene)
{
	char	*trimmed;
	int		result;

	if (scene->map_started)
		return (process_map_line(line, scene));
	trimmed = skip_spaces(line);
	if (*trimmed == '\0')
		return (1);
	result = handle_texture_line(trimmed, scene->game);
	if (result != -1)
		return (result);
	result = handle_color_line(trimmed, scene);
	if (result != -1)
		return (result);
	if (looks_like_map_line(line))
	{
		scene->map_started = 1;
		return (process_map_line(line, scene));
	}
	return (print_error("Invalid identifier before map description"));
}

static int	finalize_scene(t_scene *scene)
{
	if (!scene->map_started)
		return (print_error("Map section not found"));
	if (scene->map_height == 0)
		return (print_error("Empty map"));
	if (!scene->floor_found && !scene->ceiling_found)
		return (print_error("Missing floor and ceiling colors"));
	if (!scene->floor_found)
		return (print_error("Missing floor color"));
	if (!scene->ceiling_found)
		return (print_error("Missing ceiling color"));
	if (scene->game->floor_color == scene->game->ceiling_color)
		return (print_error("Floor and ceiling colors must differ"));
	scene->game->map = list_to_array(scene->map_lines, scene->map_height);
	if (!scene->game->map)
		return (print_error("Failed to allocate map"));
	scene->game->map_height = scene->map_height;
	scene->game->map_width = scene->map_width;
	return (1);
}

static void	clear_map_lines(t_list **lines)
{
	ft_lstclear(lines, free);
}

int	parse_scene(const char *filename, t_game *game)
{
	int		fd;
	char	*line;
	char	*tmp;
	t_scene	scene;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Cannot open file"));
	ft_bzero(&scene, sizeof(scene));
	scene.game = game;
	tmp = NULL;
	while ((line = get_next_line(fd, &tmp)) != NULL)
	{
		if (!process_scene_line(line, &scene))
		{
			free(line);
			free_gnl_tmp(&tmp);
			clear_map_lines(&scene.map_lines);
			close(fd);
			return (0);
		}
		free(line);
	}
	free_gnl_tmp(&tmp);
	close(fd);
	if (!finalize_scene(&scene))
	{
		clear_map_lines(&scene.map_lines);
		return (0);
	}
	return (1);
}
