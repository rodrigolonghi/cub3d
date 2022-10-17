/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:41:36 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/17 19:50:53 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	walk_up(t_game *game)
{
	game->velocity = create_vector(game->player_dir.x, game->player_dir.y);
	game->velocity = vector_mul_scal(game->velocity, game->movement_speed);
}

static void	walk_down(t_game *game)
{
	game->velocity = create_vector(game->player_dir.x, game->player_dir.y);
	game->velocity = vector_mul_scal(game->velocity,
			-1.0 * game->movement_speed);
}

static void	stop_walking(t_game *game)
{
	game->velocity = vector_mul_scal(game->velocity,
			0.0 * game->movement_speed);
}

static void	update_input(t_game *game)
{
	game->velocity = vector_mul_scal(game->velocity,
			1.0 / 60.0 * game->movement_speed);
	game->player_pos = vector_add(game->player_pos, game->velocity);
}

void	refresh_player(t_game *game)
{
	walk_up(game);
	walk_down(game);
	stop_walking(game);
	update_input(game);
}
