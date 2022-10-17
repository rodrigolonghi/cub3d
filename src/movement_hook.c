/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:52:09 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/17 18:34:32 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	go_up(t_game *game)
{
	int	x;
	int	y;

	if (check_movement(game, -1, 0))
	{
		x = (int)game->player_pos.x;
		y = (int)game->player_pos.y;
		game->map.coordinates[x][y] = '0';
		game->player_pos.x--;
		game->map.coordinates[x][y] = game->player_orient;
	}
	calculate(game);
}

void	go_down(t_game *game)
{
	int	x;
	int	y;

	if (check_movement(game, 1, 0))
	{
		x = (int)game->player_pos.x;
		y = (int)game->player_pos.y;
		game->map.coordinates[x][y] = '0';
		game->player_pos.x++;
		game->map.coordinates[x][y] = game->player_orient;
	}
	calculate(game);
}
