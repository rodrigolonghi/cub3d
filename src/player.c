/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:41:36 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/24 23:26:30 by acarneir         ###   ########.fr       */
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

static t_vec	check_square_collision(
	t_game *game, t_vec new_pos, t_vec map_pos)
{
	t_vec	result;

	// printf("map_pos antes = [%f, %f] ", map_pos.x, map_pos.y);
	// map_pos.x = (double)((int)(map_pos.x));
	// map_pos.y = (double)((int)(map_pos.y));
	printf("map_pos = [%f, %f] ", map_pos.x, map_pos.y);
	result = create_vector(0.0, 0.0);
	printf("new_pos = [%f, %f] \n", new_pos.x, new_pos.y);
	// printf("\ncheck: %f, %f\n", new_pos.y + game->dist_wall, map_pos.y);
	// printf("coord = [%c] ", game->map.coordinates[(int)(map_pos.x)][(int)(map_pos.y)]);
	if (game->map.coordinates[(int)(map_pos.x)][(int)(map_pos.y)] != '0')
	{
		if ((new_pos.x + game->dist_wall < map_pos.x)
			|| (new_pos.x - game->dist_wall > map_pos.x + 1)
			|| (game->player_pos.y + game->dist_wall < map_pos.y)
			|| (game->player_pos.y - game->dist_wall > map_pos.y + 1))
			result.x = 1.0;
		if ((new_pos.y + game->dist_wall < map_pos.y)
			|| (new_pos.y - game->dist_wall > map_pos.y + 1)
			|| (game->player_pos.x + game->dist_wall < map_pos.x)
			|| (game->player_pos.x - game->dist_wall > map_pos.x + 1))
		{
			result.y = 1.0;
			// printf("entrou\n");
		}
		// printf("result = [%f, %f] ", result.x, result.y);
		return (result);
	}
	return (create_vector(1.0, 1.0));
}

static t_vec	get_collision_vec(t_game *game, t_vec movement)
{
	t_vec	collision_vec;
	t_vec	new_pos;
	t_vec	map_pos;

	collision_vec = create_vector(1.0, 1.0);
	// printf("antes collision_vec = [%f, %f] ", collision_vec.x, collision_vec.y);
	map_pos.x = (double)((int)(game->player_pos.x));
	map_pos.y = (double)((int)(game->player_pos.y));
	new_pos = vector_add(game->player_pos, movement);
	if (movement.x != 0.0 || movement.y != 0.0)
	{
		collision_vec = vector_mul(collision_vec, check_square_collision(game,
					new_pos, create_vector(map_pos.x - 1,
						map_pos.y - 1)));
		collision_vec = vector_mul(collision_vec, check_square_collision(game,
					new_pos, create_vector(map_pos.x - 1,
						map_pos.y)));
		collision_vec = vector_mul(collision_vec, check_square_collision(game,
					new_pos, create_vector(map_pos.x - 1,
						map_pos.y + 1)));
		collision_vec = vector_mul(collision_vec, check_square_collision(game,
					new_pos, create_vector(map_pos.x,
						map_pos.y - 1)));
		collision_vec = vector_mul(collision_vec, check_square_collision(game,
					new_pos, create_vector(map_pos.x,
						map_pos.y + 1)));
		collision_vec = vector_mul(collision_vec, check_square_collision(game,
					new_pos, create_vector(map_pos.x + 1,
						map_pos.y - 1)));
		collision_vec = vector_mul(collision_vec, check_square_collision(game,
					new_pos, create_vector(map_pos.x + 1,
						map_pos.y)));
		collision_vec = vector_mul(collision_vec, check_square_collision(game,
					new_pos, create_vector(map_pos.x + 1,
						map_pos.y + 1)));
	}
	// printf("collision_vec = [%f, %f]\n", collision_vec.x, collision_vec.y);
	return (collision_vec);
}

static void	update_input(t_game *game)
{
	t_vec	movement;
	t_vec	collision_vec;

	movement = vector_add(game->velocity, game->strafe_vel);
	collision_vec = get_collision_vec(game, movement);
	printf("player_pos = [%f, %f] ", game->player_pos.x, game->player_pos.y);
	// printf("movement = [%f, %f] ", movement.x, movement.y);
	printf("collision_vec = [%f, %f]\n", collision_vec.x, collision_vec.y);
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
	// printf("player_pos = [%f, %f]\n", game->player_pos.x, game->player_pos.y);
}
