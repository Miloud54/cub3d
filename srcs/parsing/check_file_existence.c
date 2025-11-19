/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_existence.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:31:30 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/19 16:02:37 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Checks if a file exists and can be opened
int	file_exists(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}