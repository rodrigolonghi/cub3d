/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:41:36 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/01 21:31:12 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	x_walk(t_game *game)
{
	game->strafe_vel = create_vector(game->player_dir.x, game->player_dir.y);
	game->strafe_vel = vector_rotation(game->strafe_vel, M_PI / 2,
			game->x_walk);
	game->strafe_vel = vector_mul_scal(game->strafe_vel,
			game->movement_speed * fabs(game->x_walk));
}

static void	y_walk(t_game *game)
{
	game->velocity = create_vector(game->player_dir.x, game->player_dir.y);
	game->velocity = vector_mul_scal(game->velocity,
			game->movement_speed * game->y_walk);
}

static void	update_input(t_game *game)
{
	t_vec	movement;
	// t_vec	next_pos;
	// t_vec	cam_pos;

	movement = vector_add(game->velocity, game->strafe_vel);
	// cam_pos = vector_add(game->player_pos, game->player_dir);
	// next_pos = vector_add(cam_pos, movement);
	// if (movement.x > 0.0)
	// 	if (game->map.coordinates[(int)(next_pos.x + game->dist_wall)][(int)cam_pos.y] != '0')
	// 		movement = vector_mul(movement, create_vector(0.0, 1.0));
	// if (movement.x < 0.0)
	// 	if (game->map.coordinates[(int)(next_pos.x - game->dist_wall)][(int)cam_pos.y] != '0')
	// 		movement = vector_mul(movement, create_vector(0.0, 1.0));
	// if (movement.y > 0.0)
	// 	if (game->map.coordinates[(int)cam_pos.x][(int)(next_pos.y + game->dist_wall)] != '0')
	// 		movement = vector_mul(movement, create_vector(1.0, 0.0));
	// if (movement.y < 0.0)
	// 	if (game->map.coordinates[(int)cam_pos.x][(int)(next_pos.y - game->dist_wall)] != '0')
	// 		movement = vector_mul(movement, create_vector(1.0, 0.0));
	// printf("player_pos = [%f, %f] next_pos = [%f, %f]  d[%d, %d]", game->player_pos.x, game->player_pos.y, next_pos.x, next_pos.y, (int)(next_pos.x), (int)(next_pos.y));
	// printf("movement = [%f, %f]\n", movement.x, movement.y);
	game->player_pos = vector_add(game->player_pos, movement);
	game->camera_plane = vector_rotation(game->camera_plane,
			game->rotation_speed, game->rotation);
	game->player_dir = vector_rotation(game->player_dir,
			game->rotation_speed, game->rotation);
}

void	refresh_player(t_game *game)
{
	x_walk(game);
	y_walk(game);
	update_input(game);
}
