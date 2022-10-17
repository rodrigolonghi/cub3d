/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:38:54 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/17 18:30:00 by rfelipe-         ###   ########.fr       */
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

int	key_hook(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == ESC)
		close_game(game);
	if (key == UP)
		go_up(game);
	else if (key == DOWN)
		go_down(game);
	// else if (key == LEFT)
	// 	go_left(game);
	// else if (key == RIGHT)
	// 	go_right(game);
	// else if (key == ARROW_LEFT)
	// 	turn_left(game);
	// else if (key == ARROW_RIGHT)
	// 	turn_right(game);
	return (0);
}
