#include "../inc/cub3d.h"

static int	set_color(char identifier, char *line, int *color, int *found)
{
	if (*found)
	{
		if (identifier == 'F')
			return (print_error("Duplicate floor color definition"));
		return (print_error("Duplicate ceiling color definition"));
	}
	if (!parse_color_line(line, identifier, color))
		return (0);
	*found = 1;
	return (1);
}

static int	handle_color_line(char *line, t_color *state)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (*trimmed == '\0')
		return (1);
	if (*trimmed == 'F')
		return (set_color('F', trimmed, state->floor_color,
				&state->floor_found));
	if (*trimmed == 'C')
		return (set_color('C', trimmed, state->ceiling_color,
				&state->ceiling_found));
	return (1);
}

static int	read_color_lines(int fd, t_color *state)
{
	char	*tmp;
	char	*line;

	tmp = NULL;
	while ((line = get_next_line(fd, &tmp)) != NULL)
	{
		if (!handle_color_line(line, state))
		{
			free(line);
			free_gnl_tmp(&tmp);
			return (0);
		}
		free(line);
		if (state->floor_found && state->ceiling_found)
			break ;
	}
	free_gnl_tmp(&tmp);
	return (1);
}

static int	finalize_colors(t_color *state, int *floor_color, int *ceiling_color)
{
	if (!state->floor_found && !state->ceiling_found)
		return (print_error("Missing floor and ceiling colors"));
	if (!state->floor_found)
		return (print_error("Missing floor color"));
	if (!state->ceiling_found)
		return (print_error("Missing ceiling color"));
	if (*floor_color == *ceiling_color)
		return (print_error("Floor and ceiling colors must differ"));
	return (1);
}

int	parse_colors(const char *filename, int *floor_color, int *ceiling_color)
{
	int		fd;
	t_color	state;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Cannot open file"));
	ft_bzero(&state, sizeof(state));
	state.floor_color = floor_color;
	state.ceiling_color = ceiling_color;
	if (!read_color_lines(fd, &state))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (finalize_colors(&state, floor_color, ceiling_color));
}
