/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:41:36 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/17 22:24:57 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	y_walk(t_game *game)
{
	game->velocity = create_vector(game->player_dir.x, game->player_dir.y);
	game->velocity = vector_mul_scal(game->velocity,
			game->movement_speed * game->y_walk);
}

static void	update_input(t_game *game)
{
	game->velocity = vector_mul_scal(game->velocity,
			1.0 / 60.0 * game->movement_speed);
	game->player_pos = vector_add(game->player_pos, game->velocity);
	game->camera_plane = vector_rotation(game->camera_plane,
			game->rotation_speed, game->rotation);
	game->player_dir = vector_rotation(game->player_dir,
			game->rotation_speed, game->rotation);
}

void	refresh_player(t_game *game)
{
	y_walk(game);
	update_input(game);
}
