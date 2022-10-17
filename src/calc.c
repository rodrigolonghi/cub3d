/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:28 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/17 18:23:58 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	fill_background(t_game *game)
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
				game->map.pixel_map[i][j] = encode_rgb(game->floor);
			else
				game->map.pixel_map[i][j] = encode_rgb(game->ceilling);
			i++;
		}
		j--;
	}
}

static void	calculate_current_ray(t_game *game, int i)
{
	game->multiplier = (2.0 * ((double)(i) / (double)(WIDTH))) - 1.0;
	game->camera_pixel = vector_mul_scal(game->camera_plane, game->multiplier);
	game->ray_dir = vector_add(game->player_dir, game->camera_pixel);
	// printf("i2 = %d ", i);
	// printf("mul = %f ", game->multiplier);
	// printf("pDir = [%f, %f] ", game->player_dir.x, game->player_dir.y);
	// printf("cpx = [%f, %f] ", game->camera_pixel.x, game->camera_pixel.y);
	// printf("rayDir = [%f, %f] ", game->ray_dir.x, game->ray_dir.y);
}

static void	calculate_dda_variables(t_game *game)
{
	if (game->ray_dir.x == 0.0)
	{
		game->delta_dist_x = 1.0;
		game->delta_dist_y = 0.0;
	}
	else
		if (game->ray_dir.y != 0.0)
			game->delta_dist_x = fabs(1.0 / game->ray_dir.x);
	if (game->ray_dir.y == 0.0)
	{
		game->delta_dist_x = 0.0;
		game->delta_dist_y = 1.0;
	}
	else
		if (game->ray_dir.x != 0.0)
			game->delta_dist_y = fabs(1.0 / game->ray_dir.y);
	if (game->ray_dir.x < 0.0)
	{
		game->dist_to_side_x = (game->player_pos.x - game->map_pos.x)
			* game->delta_dist_x;
		game->step_x = -1.0;
	}
	else
	{
		game->dist_to_side_x = (game->player_pos.x + 1.0 - game->map_pos.x)
			* game->delta_dist_x;
		game->step_x = 1.0;
	}
	if (game->ray_dir.y < 0.0)
	{
		game->dist_to_side_y = (game->player_pos.y - game->map_pos.y)
			* game->delta_dist_y;
		game->step_y = -1.0;
	}
	else
	{
		game->dist_to_side_y = (game->player_pos.y + 1.0 - game->map_pos.y)
			* game->delta_dist_y;
		game->step_y = 1.0;
	}
}

static void	execute_dda(t_game *game)
{
	int		hit;
	double	dda_line_size_x;
	double	dda_line_size_y;

	dda_line_size_x = game->dist_to_side_x;
	dda_line_size_y = game->dist_to_side_y;
	game->hit_pos = create_vector(game->map_pos.x, game->map_pos.y);
	hit = 0;
	while (hit == 0)
	{
		if (dda_line_size_x < dda_line_size_y)
		{
			game->hit_pos.x += game->step_x;
			dda_line_size_x += game->delta_dist_x;
			game->hit_side = 0;
		}
		else
		{
			game->hit_pos.y += game->step_y;
			dda_line_size_y += game->delta_dist_y;
			game->hit_side = 1;
		}
		if (game->map.coordinates[(int)(game->hit_pos.x)]
			[(int)(game->hit_pos.y)] != '0')
			hit = 1;
	}
}

static void	calculate_perpendicular_dist(t_game *game)
{
	if (game->hit_side == 0)
		game->perp_dist = fabs(game->hit_pos.x - game->player_pos.x
				+ ((1.0 - game->step_x) / 2.0)) / game->ray_dir.x;
	else
		game->perp_dist = fabs(game->hit_pos.y - game->player_pos.y
				+ ((1.0 - game->step_y) / 2.0)) / game->ray_dir.y;
}

static void	draw_wall(t_game *game, t_color wall_color, int i)
{
	double	wall_height;
	double	wall_start_y;
	double	wall_end_y;
	int		j;
	int		end;

	wall_height = (double)(HEIGHT) / game->perp_dist;
	wall_start_y = (double)(HEIGHT) / 2.0 - wall_height / 2.0;
	wall_end_y = (double)(HEIGHT) / 2.0 + wall_height / 2.0;
	// printf("perp = %f,  wh = %f, start = %f, end = %f\n", game->perp_dist, wall_height, wall_start_y, wall_end_y);
	if (wall_start_y < wall_end_y)
	{
		j = (int)(wall_start_y);
		end = (int)(wall_end_y);
	}
	else
	{
		j = (int)(wall_end_y);
		end = (int)(wall_start_y);
	}
	// j = (int)(wall_start_y);
	// end = (int)(wall_end_y);
	while (j < end)
	{
		// printf("i = %d, j = %d\n", i, j);
		game->map.pixel_map[i][j] = encode_rgb(wall_color);
		j++;
	}
}

void	calculate(t_game *game)
{
	int		i;
	t_color	wall_color;

	fill_background(game);
	i = 0;
	while (i < WIDTH)
	{
		// printf("start\n");
		// printf("i = %d ", i);
		calculate_current_ray(game, i);
		calculate_dda_variables(game);
		execute_dda(game);
		calculate_perpendicular_dist(game);
		if (game->hit_side)
			wall_color = create_color(255, 0, 0);
		else
			wall_color = create_color(128, 0, 0);
		draw_wall(game, wall_color, i);
		i++;
	}
	// printf("end\n");
}
