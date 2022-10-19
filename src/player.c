/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:41:36 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/18 21:13:06 by rfelipe-         ###   ########.fr       */
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

static t_vec	get_collision_vec(t_game *game, t_vec movement)
{
	t_vec	new_pos;
	t_vec	collision_vec;

	new_pos = vector_add(game->player_pos, movement);
	collision_vec = create_vector(1.0, 1.0);
	if (movement.x > 0.0 || movement.y > 0.0)
	{
		if (game->map.coordinates[(int)(new_pos.x + game->dist_wall)]
			[(int)game->player_pos.y] != '0')
			collision_vec.x = 0.0;
		if (game->map.coordinates[(int)game->player_pos.x]
			[(int)(new_pos.y + game->dist_wall)] != '0')
			collision_vec.y = 0.0;
	}
	return (collision_vec);
}

static void	update_input(t_game *game)
{
	t_vec	movement;
	t_vec	collision_vec;

	game->velocity = vector_mul_scal(game->velocity, game->movement_speed);
	game->strafe_vel = vector_mul_scal(game->strafe_vel, game->movement_speed);
	movement = vector_add(game->velocity, game->strafe_vel);
	collision_vec = get_collision_vec(game, movement);
	movement = vector_mul(movement, collision_vec);
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
