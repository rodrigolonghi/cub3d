/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:38:54 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/17 21:28:03 by acarneir         ###   ########.fr       */
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
		game->y_walk = 1;
	if (key == DOWN)
		game->y_walk = -1;
	if (key == LEFT)
		game->x_walk = -1;
	if (key == RIGHT)
		game->x_walk = 1;
	if (key == ARROW_LEFT)
		game->turn = -1;
	if (key == ARROW_RIGHT)
		game->turn = 1;
}

static void	key_release(int key, t_game *game)
{
	if (key == UP)
		game->y_walk = 0;
	if (key == DOWN)
		game->y_walk = 0;
	if (key == LEFT)
		game->x_walk = 0;
	if (key == RIGHT)
		game->x_walk = 0;
	if (key == ARROW_LEFT)
		game->turn = 0;
	if (key == ARROW_RIGHT)
		game->turn = 0;
}

static void	key_hook(int key, void *param, int key_type)
{
	t_game	*game;

	game = (t_game *)param;
	// printf("keyhook = %d, keytype = %d \n", key, key_type);
	if (key == ESC)
		close_game(game);
	else if (key_type == PRESS)
		key_press(key, game);
	else if (key_type == RELEASE)
		key_release(key, game);
}

int	press(int key, t_game *game)
{
	key_hook(key, game, PRESS);
	return (0);
}

int	release(int key, t_game *game)
{
	key_hook(key, game, RELEASE);
	return (0);
}
