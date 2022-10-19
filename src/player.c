/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:41:36 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/18 23:45:18 by acarneir         ###   ########.fr       */
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
	printf("player_pos0 = [%f, %f] ", game->player_pos.x, game->player_pos.y);
	game->player_pos = vector_add(game->player_pos, game->velocity);
	printf("player_pos1 = [%f, %f] ", game->player_pos.x, game->player_pos.y);
	game->camera_plane = vector_rotation(game->camera_plane,
			game->rotation_speed, game->rotation);
	game->player_dir = vector_rotation(game->player_dir,
			game->rotation_speed, game->rotation);
}

void	refresh_player(t_game *game)
{
	y_walk(game);
	update_input(game);
	printf("map_pos0 = [%f, %f] ", game->map_pos.x, game->map_pos.y);
	game->map_pos.x = (int)(game->player_pos.x+0.01);
	game->map_pos.y = (int)(game->player_pos.y+0.01);
	printf("map_pos1 = [%f, %f]\n", game->map_pos.x, game->map_pos.y);
}
