/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedidier <emiliedidier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:20:12 by emiliedidie       #+#    #+#             */
/*   Updated: 2025/11/20 16:52:46 by emiliedidie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_line_empty(char *line)
{
	if (*line == '\0' || *line == '\n' || *line == '\r')
		return (1);
	return (0);
}

static int	process_line(char *line, t_list **lines, t_map *state)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (!state->started)
	{
		if (is_line_empty(trimmed) || is_map_identifier(trimmed))
			return (1);
		state->started = 1;
	}
	if (is_line_empty(trimmed))
	{
		state->ended = 1;
		return (1);
	}
	if (state->ended)
		return (print_error("Map must be the last element of the file"));
	if (!append_map_line(lines, line, &state->width))
		return (0);
	state->height++;
	return (1);
}

static int	build_map_lines(int fd, t_list **lines, int *height, int *width)
{
	char	*tmp;
	char	*line;
	t_map	state;

	ft_bzero(&state, sizeof(state));
	tmp = NULL;
	while ((line = get_next_line(fd, &tmp)) != NULL)
	{
		if (!process_line(line, lines, &state))
		{
			free(line);
			free_gnl_tmp(&tmp);
			return (0);
		}
		free(line);
	}
	free_gnl_tmp(&tmp);
	if (!state.started)
		return (print_error("Map section not found"));
	if (state.height == 0)
		return (print_error("Empty map"));
	*height = state.height;
	*width = state.width;
	return (1);
}

static int	finalize_map(t_game *game, t_list *lines, int height, int width)
{
	game->map = list_to_array(lines, height);
	if (!game->map)
		return (print_error("Failed to allocate map"));
	game->map_height = height;
	game->map_width = width;
	return (1);
}

int	parse_map(const char *filename, t_game *game)
{
	int		fd;
	t_list	*lines;
	int		height;
	int		width;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Cannot open file"));
	lines = NULL;
	height = 0;
	width = 0;
	if (!build_map_lines(fd, &lines, &height, &width))
	{
		close(fd);
		ft_lstclear(&lines, free);
		return (0);
	}
	close(fd);
	return (finalize_map(game, lines, height, width));
}
