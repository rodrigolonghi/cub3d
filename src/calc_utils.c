/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:38:31 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/11 18:12:00 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_background(t_game *g)
{
	int		i;
	int		j;

	j = HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < WIDTH - 1)
		{
			if (j < HEIGHT / 2)
				g->file.map.pixel_map[i][j] = encode_rgb(g->file.floor);
			else
				g->file.map.pixel_map[i][j] = encode_rgb(g->file.ceilling);
			i++;
		}
		j--;
	}
}

void	calculate_current_ray(t_game *game, int i)
{
	game->dda.multiplier = (2.0 * ((double)(i) / (double)(WIDTH))) - 1.0;
	game->dda.camera_pixel = vector_mul_scal(
			game->dda.camera_plane, game->dda.multiplier);
	game->dda.ray_dir = vector_add(game->p.player_dir, game->dda.camera_pixel);
}

void	get_dist_to_side(t_game *game)
{
	if (game->dda.ray_dir.x < 0.0)
	{
		game->dda.dist_to_side_x = (game->p.player_pos.x - game->map_pos.x)
			* game->dda.delta_dist_x;
		game->dda.step_x = -1.0;
	}
	else
	{
		game->dda.dist_to_side_x = (game->map_pos.x + 1.0
				- game->p.player_pos.x) * game->dda.delta_dist_x;
		game->dda.step_x = 1.0;
	}
	if (game->dda.ray_dir.y < 0.0)
	{
		game->dda.dist_to_side_y = (game->p.player_pos.y - game->map_pos.y)
			* game->dda.delta_dist_y;
		game->dda.step_y = -1.0;
	}
	else
	{
		game->dda.dist_to_side_y = (game->map_pos.y + 1.0
				- game->p.player_pos.y) * game->dda.delta_dist_y;
		game->dda.step_y = 1.0;
	}
}

void	get_delta_dist(t_game *game)
{
	if (game->dda.ray_dir.x == 0.0)
	{
		game->dda.delta_dist_x = 1.0;
		game->dda.delta_dist_y = 0.0;
	}
	else
		if (game->dda.ray_dir.y != 0.0)
			game->dda.delta_dist_x = fabs(1.0 / game->dda.ray_dir.x);
	if (game->dda.ray_dir.y == 0.0)
	{
		game->dda.delta_dist_x = 0.0;
		game->dda.delta_dist_y = 1.0;
	}
	else
		if (game->dda.ray_dir.x != 0.0)
			game->dda.delta_dist_y = fabs(1.0 / game->dda.ray_dir.y);
}

void	calculate_dda_variables(t_game *game)
{
	game->map_pos.x = (int)(game->p.player_pos.x);
	game->map_pos.y = (int)(game->p.player_pos.y);
	get_delta_dist(game);
	get_dist_to_side(game);
}
