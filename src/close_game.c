/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:41:31 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/10 19:42:11 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.coordinates)
	{
		while (i < game->map.rows)
		{
			free(game->map.coordinates[i]);
			i++;
		}
		free(game->map.coordinates);
	}
}

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
