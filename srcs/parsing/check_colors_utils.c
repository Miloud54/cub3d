#include "../inc/cub3d.h"

static int	component_from_part(char *part, int *value)
{
	char	*trimmed;

	trimmed = ft_strtrim(part, COLOR_WHITESPACES);
	if (!trimmed)
		return (print_error("Failed to trim color component"));
	if (!is_numeric_string(trimmed))
		return (free(trimmed), print_error("Color components must be numeric"));
	*value = ft_atoi(trimmed);
	free(trimmed);
	if (*value < 0 || *value > 255)
		return (print_error("Color components must be between 0 and 255"));
	return (1);
}

static int	validate_rgb_parts(char **parts, int rgb[3])
{
	int	count;
	int	i;

	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
		return (print_error("Color needs exactly 3 values"));
	i = 0;
	while (i < 3)
	{
		if (!component_from_part(parts[i], &rgb[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_rgb_triplet(char *value_str, int *out_color)
{
	char	**parts;
	int		rgb[3];
	int		success;

	parts = ft_split(value_str, ',');
	if (!parts)
		return (print_error("Failed to split color values"));
	success = validate_rgb_parts(parts, rgb);
	ft_free_split(&parts);
	if (!success)
		return (0);
	*out_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}
