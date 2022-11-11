/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:34:40 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/11 18:05:47 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	game_loop(t_game *game)
{
	refresh_player(game);
	calculate(game);
	render(game);
	return (0);
}

static void	initiate(t_game *game)
{
	game->file.texture = malloc(4 * sizeof(t_texture));
	game->mlx = NULL;
	game->win = NULL;
	game->rotation = 0;
	game->x_walk = 0.0;
	game->y_walk = 0.0;
	game->error = FALSE;
	game->dist_wall = 1.5;
	game->file.floor.r = -1;
	game->file.map.rows = 0;
	game->file.map.cols = 0;
	game->file.ceilling.r = -1;
	game->file.map.coordinates = NULL;
	game->file.texture[0].addr = NULL;
	game->file.texture[1].addr = NULL;
	game->file.texture[2].addr = NULL;
	game->file.texture[3].addr = NULL;
	game->file.texture[0].img.ptr = NULL;
	game->file.texture[1].img.ptr = NULL;
	game->file.texture[2].img.ptr = NULL;
	game->file.texture[3].img.ptr = NULL;
	game->p.movement_speed = 1.0 / 60.0;
	game->p.rotation_speed = 1.0 / 60.0;
}

void	start_game(t_game *game, int argc, char *argv[])
{
	initiate(game);
	game->mlx = mlx_init();
	check_params(game, argc, argv);
	check_map(game, argv[1]);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	mlx_hook(game->win, 2, 1L << 0, press, game);
	mlx_hook(game->win, 3, 1L << 1, release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
}
