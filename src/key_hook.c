/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:38:54 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/17 19:30:35 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_movement(t_game *g, int x, int y)
{
	x = g->player_pos.x + x;
	y = g->player_pos.y + y;
	if (g->map.coordinates[x][y] == '0')
		return (TRUE);
	return (FALSE);
}

static void	key_press(int key, t_game *game)
{
	if (key == UP)
		game->walk = -1;
	if (key == DOWN)
		game->walk = 1;
	if (key == LEFT)
		game->walk = -1;
	if (key == RIGHT)
		game->walk = 1;
	if (key == ARROW_LEFT)
		game->turn = -1;
	if (key == ARROW_RIGHT)
		game->turn = 1;
}

static void	key_release(int key, t_game *game)
{
	if (key == UP)
		game->walk = 0;
	if (key == DOWN)
		game->walk = 0;
	if (key == LEFT)
		game->walk = 0;
	if (key == RIGHT)
		game->walk = 0;
	if (key == ARROW_LEFT)
		game->turn = 0;
	if (key == ARROW_RIGHT)
		game->turn = 0;
}

int	key_hook(int key, void *param, int key_type)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == ESC)
		close_game(game);
	else if (key_type == PRESS)
		key_press(key, game);
	else
		key_release(key, game);
	return (0);
}
