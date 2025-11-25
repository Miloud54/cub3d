/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:51:32 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/25 18:20:30 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_valid_extension(char *filename)
{
	char	*dot_pos;
	char	*first_dot;
	int		len;

	len = ft_strlen(filename);
	if (!filename || len < 4)
	{
		write(2, "Error\nInvalid filename\n", 23);
		return (0);
	}
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
	{
		write(2, "Error\nWrong file extension (must be .cub)\n", 42);
		return (0);
	}
	first_dot = ft_strchr(filename, '.');
	dot_pos = ft_strrchr(filename, '.');
	if (first_dot != dot_pos)
	{
		write(2, "Error\nMultiple extensions not allowed\n", 38);
		return (0);
	}
	return (1);
}

static int	check_xpm_extension_validity(char *filename, int len)
{
	if (!filename || len < 4)
	{
		write(2, "Error\nInvalid filename\n", 23);
		return (0);
	}
	if (ft_strcmp(filename + len - 4, ".xpm") != 0)
	{
		write(2, "Error\nWrong file extension (must be .xpm)\n", 42);
		return (0);
	}
	return (1);
}

static int	check_xpm_multiple_extensions(char *filename)
{
	char	*dot_pos;
	char	*basename_start;
	char	*first_dot_in_name;

	basename_start = ft_strrchr(filename, '/');
	if (basename_start)
		basename_start++;
	else
		basename_start = filename;
	first_dot_in_name = ft_strchr(basename_start, '.');
	dot_pos = ft_strrchr(basename_start, '.');
	if (first_dot_in_name != dot_pos)
	{
		write(2, "Error\nMultiple extensions not allowed\n", 38);
		return (0);
	}
	return (1);
}

int	is_valid_extension_xpm(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (!check_xpm_extension_validity(filename, len))
		return (0);
	if (!check_xpm_multiple_extensions(filename))
		return (0);
	return (1);
}
