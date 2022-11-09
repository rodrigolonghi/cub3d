/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:28 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/08 21:43:49 by acarneir         ###   ########.fr       */
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
	// printf("pDir = [%f, %f] \n", game->player_dir.x, game->player_dir.y);
	// printf("cpx = [%f, %f] ", game->camera_pixel.x, game->camera_pixel.y);
	// printf("rayDir = [%f, %f] ", game->ray_dir.x, game->ray_dir.y);
}

static void	calculate_dda_variables(t_game *game)
{
	game->map_pos.x = (int)(game->player_pos.x);
	game->map_pos.y = (int)(game->player_pos.y);
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
		game->dist_to_side_x = (game->map_pos.x + 1.0 - game->player_pos.x)
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
		game->dist_to_side_y = (game->map_pos.y + 1.0 - game->player_pos.y)
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
		if (game->map.coordinates[(int)(game->hit_pos.y)]
			[(int)(game->hit_pos.x)] != '0')
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
// 	if (game->hit_side == 0)
// 		game->perp_dist = game->dist_to_side_x - game->delta_dist_x;
// 	else
// 		game->perp_dist = game->dist_to_side_y - game->delta_dist_y;
}

static int	calculate_wall_texture(t_game *game, int i, int j)
{
	double	wall_x;
	int		tex_x;
	double	wall_y;

	if(i == j){
		
	}
	if (!game->hit_side)
		wall_x = game->player_pos.y + game->perp_dist * game->ray_dir.y;
	else
		wall_x = game->player_pos.x + game->perp_dist * game->ray_dir.x;
	wall_x -= (int)wall_x;
	tex_x = (int)(wall_x * (double)game->no.width);
	wall_y =  (double)game->no.height * (j - (int)game->wall_start_y) / game->wall_height;
	printf("[%d][%d] wall_x = %f tex_x = %d wall_y = %f wall_height = %f ", i, j, wall_x, tex_x, wall_y, game->wall_height);
	// return (*(unsigned int *)(game->so.img.data) + (wall_y * game->no.img.line_length + wall_x * (game->no.img.bits_per_pixel / 8)));
	return (*(unsigned int *)(game->no.img.data
		+ ((int)wall_y * game->no.img.line_length + (int)tex_x
			* (game->no.img.bits_per_pixel / 8))));
}

static void	draw_wall(t_game *game, t_color wall_color, int i)
{
	int		j;
	int		end;
	int		color;
	
	if (wall_color.r == 0){
		
	}
	if (fabs(game->perp_dist) < 1.0)
		game->wall_height = (double)(HEIGHT);
	else
		game->wall_height = (double)(HEIGHT) / game->perp_dist;
	game->wall_start_y = (double)(HEIGHT) / 2.0 - game->wall_height / 2.0;
	game->wall_end_y = (double)(HEIGHT) / 2.0 + game->wall_height / 2.0;
	// printf("perp = %f,  wh = %f, start = %f, end = %f\n", game->perp_dist, wall_height, wall_start_y, wall_end_y);
	if (game->wall_start_y < game->wall_end_y)
	{
		j = (int)(game->wall_start_y);
		end = (int)(game->wall_end_y);
	}
	else
	{
		j = (int)(game->wall_end_y);
		end = (int)(game->wall_start_y);
	}
	// j = (int)(wall_start_y);
	// end = (int)(wall_end_y);
	while (j < end)
	{
		// printf("i = %d, j = %d\n", i, j);
		color = calculate_wall_texture(game, i, j);
		printf("color = %d\n ",color);
		// game->map.pixel_map[i][j] = encode_rgb(wall_color);
		game->map.pixel_map[i][j] = color;
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
		calculate_current_ray(game, i);
		calculate_dda_variables(game);
		execute_dda(game);
		calculate_perpendicular_dist(game);
		
		// if (game->hit_side)
		// 	wall_color = create_color(255, 0, 0);
		// else
		// 	wall_color = create_color(128, 0, 0);
		draw_wall(game, wall_color, i);
		i++;
	}
}
