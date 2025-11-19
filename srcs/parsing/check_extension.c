/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:51:32 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/19 13:52:08 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_valid_extension(char *filename)
{
	int		len;

	len = ft_strlen(filename);
	if (len < 4)
	{
		write(2, "Error\nWrong file extension\n", 27);
		return (0);
	}
	if (filename[len - 1] == 'b' && filename[len - 2] == 'u'
		&& filename[len - 3] == 'c' && filename[len - 4] == '.')
		return (1);
	write(2, "Error\nWrong file extension\n", 27);
	return (0);
}