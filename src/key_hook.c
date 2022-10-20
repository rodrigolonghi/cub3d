/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:38:54 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/19 21:47:26 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	key_press(int key, t_game *game)
{
	if (key == UP)
		game->y_walk = 1;
	if (key == DOWN)
		game->y_walk = -1;
	if (key == LEFT)
		game->x_walk = 1;
	if (key == RIGHT)
		game->x_walk = -1;
	if (key == ARROW_LEFT)
		game->rotation = 1;
	if (key == ARROW_RIGHT)
		game->rotation = -1;
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
		game->rotation = 0;
	if (key == ARROW_RIGHT)
		game->rotation = 0;
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
