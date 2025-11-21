/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:56:02 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/11/21 12:18:20 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	handle_input(int keycode, t_game *game)
{
	if (keycode == 65307)
		return (close_game(game));
	return (0);
}
