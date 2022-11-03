/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:34:40 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/03 00:02:33 by rfelipe-         ###   ########.fr       */
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
	game->mlx = NULL;
	game->win = NULL;
	game->movement_speed = 1.0 / 60.0;
	game->rotation_speed = 1.0 / 60.0;
	game->rotation = 0;
	game->x_walk = 0.0;
	game->y_walk = 0.0;
	game->dist_wall = 0.0;
	game->no.addr = NULL;
	game->so.addr = NULL;
	game->we.addr = NULL;
	game->ea.addr = NULL;
	game->ceilling.r = -1;
	game->floor.r = -1;
	game->win_heigh = HEIGHT;
	game->win_width = WIDTH;
}

static void	start_win(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	// load_image(game);
}

void	start_game(t_game *game, int argc, char *argv[])
{
	initiate(game);
	check_params(game, argc, argv);
	check_map(game, argv[1]);
	start_win(game);
	mlx_hook(game->win, 2, 1L << 0, press, game);
	mlx_hook(game->win, 3, 1L << 1, release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
}
