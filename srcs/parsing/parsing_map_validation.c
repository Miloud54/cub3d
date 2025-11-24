/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:02:12 by emiliedidie       #+#    #+#             */
/*   Updated: 2025/11/24 15:39:28 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// Marque les espaces accessibles depuis l'extérieur (flood-fill récursif)
static void	mark_exterior_spaces(char **map, char **exterior_map, int height, int row, int col)
{
	int	len;

	if (row < 0 || row >= height || col < 0)
		return;
	len = ft_strlen(map[row]);
	if (col >= len)
		return;
	
	// Si déjà marqué ou si c'est un mur, arrêter
	if (exterior_map[row][col] == 'X' || map[row][col] == '1')
		return;
	
	// Marquer cette position comme extérieure
	exterior_map[row][col] = 'X';
	
	// Continuer le flood-fill dans les 4 directions
	mark_exterior_spaces(map, exterior_map, height, row - 1, col);
	mark_exterior_spaces(map, exterior_map, height, row + 1, col);
	mark_exterior_spaces(map, exterior_map, height, row, col - 1);
	mark_exterior_spaces(map, exterior_map, height, row, col + 1);
}

// Crée une map pour marquer les espaces extérieurs
static char	**create_exterior_map(t_game *game)
{
	char	**exterior_map;
	int		row;
	int		col;
	int		max_width;
	
	// Trouver largeur max et allouer
	max_width = 0;
	for (row = 0; row < game->map_height; row++)
	{
		int len = ft_strlen(game->map[row]);
		if (len > max_width)
			max_width = len;
	}
	
	exterior_map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!exterior_map)
		return (NULL);
		
	for (row = 0; row < game->map_height; row++)
	{
		exterior_map[row] = ft_calloc(max_width + 1, sizeof(char));
		if (!exterior_map[row])
		{
			while (--row >= 0)
				free(exterior_map[row]);
			free(exterior_map);
			return (NULL);
		}
	}
	exterior_map[game->map_height] = NULL;
	
	// Commencer flood-fill depuis tous les bords
	for (row = 0; row < game->map_height; row++)
	{
		mark_exterior_spaces(game->map, exterior_map, game->map_height, row, 0); // Bord gauche
		col = ft_strlen(game->map[row]) - 1;
		if (col >= 0)
			mark_exterior_spaces(game->map, exterior_map, game->map_height, row, col); // Bord droit
	}
	for (col = 0; col < max_width; col++)
	{
		mark_exterior_spaces(game->map, exterior_map, game->map_height, 0, col); // Bord haut
		mark_exterior_spaces(game->map, exterior_map, game->map_height, game->map_height - 1, col); // Bord bas
	}
	
	return (exterior_map);
}

// Libère la exterior_map
static void	free_exterior_map(char **exterior_map, int height)
{
	int row = 0;
	while (row < height)
		free(exterior_map[row++]);
	free(exterior_map);
}









// Cette fonction sera remplacée par une version qui utilise exterior_map
static int	is_void_with_exterior_check(char **map, char **exterior_map, int height, int row, int col)
{
	int	len;

	// Hors limites = void
	if (row < 0 || row >= height || col < 0)
		return (1);
	len = ft_strlen(map[row]);
	if (col >= len)
		return (1);
	
	// Si c'est un mur, ce n'est pas void
	if (map[row][col] == '1')
		return (0);
	
	// Si c'est un espace marqué comme extérieur, c'est void
	if (map[row][col] == ' ' && exterior_map[row][col] == 'X')
		return (1);
	
	// Sinon (espace intérieur, sol, joueur), ce n'est pas void
	return (0);
}

static int	validate_cell_with_exterior(char **map, char **exterior_map, int height, int row, int col)
{
	// Pour chaque cellule de jeu (0 ou joueur), vérifier qu'elle n'est pas adjacente au vide
	if (is_void_with_exterior_check(map, exterior_map, height, row - 1, col) || 
		is_void_with_exterior_check(map, exterior_map, height, row + 1, col) ||
		is_void_with_exterior_check(map, exterior_map, height, row, col - 1) || 
		is_void_with_exterior_check(map, exterior_map, height, row, col + 1))
		return (print_error("Map not closed: player/floor space adjacent to exterior"));
	return (1);
}



int	validate_map_structure(t_game *game)
{
	char	**exterior_map;
	int		player_count;
	int		row;
	int		col;

	player_count = 0;
	exterior_map = create_exterior_map(game);
	if (!exterior_map)
		return (print_error("Failed to create exterior map"));
	
	// Vérifier chaque cellule avec la nouvelle logique
	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (game->map[row][col])
		{
			if (is_player(game->map[row][col]))
			{
				player_count++;
				// Vérifier que le joueur n'est pas dans un espace extérieur
				if (game->map[row][col] != '0' && game->map[row][col] != '1')
				{
					if (game->map[row][col] == ' ' && exterior_map[row][col] == 'X')
					{
						free_exterior_map(exterior_map, game->map_height);
						return (print_error("Player cannot be in exterior space"));
					}
				}
			}
			
			if ((game->map[row][col] == '0' || is_player(game->map[row][col]))
				&& !validate_cell_with_exterior(game->map, exterior_map, game->map_height, row, col))
			{
				free_exterior_map(exterior_map, game->map_height);
				return (0);
			}
			col++;
		}
		row++;
	}
	
	free_exterior_map(exterior_map, game->map_height);
	
	if (player_count != 1)
		return (print_error("Map must contain exactly one player"));
	return (1);
}

// Fonction helper pour le rendu - détermine si un espace est extérieur
int	is_exterior_space(t_game *game, int row, int col)
{
	char	**exterior_map;
	int		result;

	if (row < 0 || row >= game->map_height || col < 0)
		return (1);
	if (col >= (int)ft_strlen(game->map[row]))
		return (1);
	if (game->map[row][col] != ' ')
		return (0); // Seuls les espaces peuvent être extérieurs
	
	exterior_map = create_exterior_map(game);
	if (!exterior_map)
		return (1); // En cas d'erreur, considérer comme extérieur
	
	result = (exterior_map[row][col] == 'X');
	free_exterior_map(exterior_map, game->map_height);
	
	return (result);
}
