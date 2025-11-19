/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:51:32 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/19 15:12:24 by bde-la-p         ###   ########.fr       */
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
