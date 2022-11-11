/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:41:36 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/11 18:46:26 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	validate_player(t_game *game)
{
	int	rows;
	int	cols;
	int	has_player;

	has_player = 0;
	rows = 0;
	while (rows < game->file.map.rows)
	{
		cols = 0;
		while (cols < game->file.map.cols)
		{
			if (cols < ft_strlen(game->file.map.coordinates[rows])
				&& game->file.map.coordinates[rows][cols] && ft_strchr("NSWE",
				game->file.map.coordinates[rows][cols]))
				has_player++;
			cols++;
		}
		rows++;
	}
	if (!has_player)
		throw_error("No player was found!", game);
	if (has_player > 1)
		throw_error("You need to put exactly one player on the map.", game);
}

static void	x_walk(t_game *game)
{
	game->p.strafe_vel = create_vector(
			game->p.player_dir.x, game->p.player_dir.y);
	game->p.strafe_vel = vector_rotation(
			game->p.strafe_vel, M_PI / 2, game->x_walk);
	game->p.strafe_vel = vector_mul_scal(
			game->p.strafe_vel, game->p.movement_speed * fabs(game->x_walk));
}

static void	y_walk(t_game *game)
{
	game->p.velocity = create_vector(
			game->p.player_dir.x, game->p.player_dir.y);
	game->p.velocity = vector_mul_scal(
			game->p.velocity, game->p.movement_speed * game->y_walk);
}

static void	update_input(t_game *game)
{
	t_vec	movement;

	movement = vector_add(game->p.velocity, game->p.strafe_vel);
	game->p.player_pos = vector_add(game->p.player_pos, movement);
	game->dda.camera_plane = vector_rotation(game->dda.camera_plane,
			game->p.rotation_speed, game->rotation);
	game->p.player_dir = vector_rotation(game->p.player_dir,
			game->p.rotation_speed, game->rotation);
}

void	refresh_player(t_game *game)
{
	x_walk(game);
	y_walk(game);
	update_input(game);
}
