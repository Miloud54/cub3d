#include "../inc/cub3d.h"

static int	parse_color_line(char *line, char identifier, int *target_color)
{
	char	*values;

	values = skip_spaces(line + 1);
	if (*values == '\0')
	{
		if (identifier == 'F')
			return (print_error("Missing floor color values"));
		return (print_error("Missing ceiling color values"));
	}
	return (parse_rgb_triplet(values, target_color));
}

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

static int	handle_color_line(char *line, int *floor_color, int *ceiling_color,
		int *floor_found, int *ceiling_found)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (*trimmed == '\0')
		return (1);
	if (*trimmed == 'F')
		return (set_color('F', trimmed, floor_color, floor_found));
	if (*trimmed == 'C')
		return (set_color('C', trimmed, ceiling_color, ceiling_found));
	return (1);
}

static int	read_color_lines(int fd, int *floor_color, int *ceiling_color,
		int *floor_found, int *ceiling_found)
{
	char	*tmp;
	char	*line;

	tmp = NULL;
	while ((line = get_next_line(fd, &tmp)) != NULL)
	{
		if (!handle_color_line(line, floor_color, ceiling_color,
				floor_found, ceiling_found))
		{
			free(line);
			free_gnl_tmp(&tmp);
			return (0);
		}
		free(line);
		if (*floor_found && *ceiling_found)
			break ;
	}
	free_gnl_tmp(&tmp);
	return (1);
}

int	parse_colors(const char *filename, int *floor_color, int *ceiling_color)
{
	int		fd;
	int		floor_found;
	int		ceiling_found;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Cannot open file"));
	floor_found = 0;
	ceiling_found = 0;
	if (!read_color_lines(fd, floor_color, ceiling_color,
			&floor_found, &ceiling_found))
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (!floor_found && !ceiling_found)
		return (print_error("Missing floor and ceiling colors"));
	if (!floor_found)
		return (print_error("Missing floor color"));
	if (!ceiling_found)
		return (print_error("Missing ceiling color"));
	if (*floor_color == *ceiling_color)
		return (print_error("Floor and ceiling colors must differ"));
	return (1);
}
