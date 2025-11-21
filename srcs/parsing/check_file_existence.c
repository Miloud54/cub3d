/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_existence.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:31:30 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/21 17:13:47 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	file_exists(const char *path)
{
	int		fd;
	ssize_t	bytes;
	char	buf;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	bytes = read(fd, &buf, 1);
	close(fd);
	if (bytes < 0 && errno == EISDIR)
		return (0);
	return (bytes >= 0);
}
