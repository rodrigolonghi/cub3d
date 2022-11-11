/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:28 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/11 18:00:07 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	execute_dda(t_game *g, int hit)
{
	double	dda_line_size_x;
	double	dda_line_size_y;

	dda_line_size_x = g->dda.dist_to_side_x;
	dda_line_size_y = g->dda.dist_to_side_y;
	g->dda.hit_pos = create_vector(g->map_pos.x, g->map_pos.y);
	while (hit == 0)
	{
		if (dda_line_size_x < dda_line_size_y)
		{
			g->dda.hit_pos.x += g->dda.step_x;
			dda_line_size_x += g->dda.delta_dist_x;
			g->dda.hit_side = 0;
		}
		else
		{
			g->dda.hit_pos.y += g->dda.step_y;
			dda_line_size_y += g->dda.delta_dist_y;
			g->dda.hit_side = 1;
		}
		if (g->file.map.coordinates[(int)(g->dda.hit_pos.y)]
			[(int)(g->dda.hit_pos.x)] != '0')
			hit = 1;
	}
}

static void	calculate_perpendicular_dist(t_game *game)
{
	if (game->dda.hit_side == 0)
		game->dda.perp_dist = fabs(game->dda.hit_pos.x - game->p.player_pos.x
				+ ((1.0 - game->dda.step_x) / 2.0)) / game->dda.ray_dir.x;
	else
		game->dda.perp_dist = fabs(game->dda.hit_pos.y - game->p.player_pos.y
				+ ((1.0 - game->dda.step_y) / 2.0)) / game->dda.ray_dir.y;
}

static int	calculate_wall_texture(t_game *g, int j)
{
	double	wall_x;
	int		tex_x;
	double	wall_y;
	int		t;

	if (g->dda.hit_side == 1 && g->dda.ray_dir.y < 0)
		t = 0;
	else if (g->dda.hit_side == 1 && g->dda.ray_dir.y > 0)
		t = 1;
	else if (g->dda.hit_side == 0 && g->dda.ray_dir.x < 0)
		t = 2;
	else
		t = 3;
	if (!g->dda.hit_side)
		wall_x = g->p.player_pos.y + fabs(g->dda.perp_dist) * g->dda.ray_dir.y;
	else
		wall_x = g->p.player_pos.x + fabs(g->dda.perp_dist) * g->dda.ray_dir.x;
	wall_x -= (int)wall_x;
	tex_x = (int)(wall_x * (double)g->file.texture[t].width);
	wall_y = (double)g->file.texture[t].height
		* (j - (int)g->dda.wall_start_y) / g->dda.wall_height;
	return (*(unsigned int *)(g->file.texture[t].img.data
		+ ((int)wall_y * g->file.texture[t].img.line_length + (int)tex_x
			* (g->file.texture[t].img.bits_per_pixel / 8))));
}

static void	draw_wall(t_game *game, int i)
{
	int	j;
	int	end;

	if (fabs(game->dda.perp_dist) < 1.0)
		game->dda.wall_height = (double)(HEIGHT);
	else
		game->dda.wall_height = (double)(HEIGHT) / game->dda.perp_dist;
	game->dda.wall_start_y = (double)(HEIGHT)
		/ 2.0 - game->dda.wall_height / 2.0;
	game->dda.wall_end_y = (double)(HEIGHT) / 2.0 + game->dda.wall_height / 2.0;
	if (game->dda.wall_start_y < game->dda.wall_end_y)
	{
		j = (int)(game->dda.wall_start_y);
		end = (int)(game->dda.wall_end_y);
	}
	else
	{
		j = (int)(game->dda.wall_end_y);
		end = (int)(game->dda.wall_start_y);
	}
	while (j < end)
	{
		game->file.map.pixel_map[i][j] = calculate_wall_texture(game, j);
		j++;
	}
}

void	calculate(t_game *game)
{
	int		i;

	fill_background(game);
	i = 0;
	while (i < WIDTH)
	{
		calculate_current_ray(game, i);
		calculate_dda_variables(game);
		execute_dda(game, 0);
		calculate_perpendicular_dist(game);
		draw_wall(game, i);
		i++;
	}
}
