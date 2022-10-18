/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:34:40 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/17 21:36:36 by rfelipe-         ###   ########.fr       */
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
	game->movement_speed = 2.0;
	game->rotation_speed = 3.0;
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
	check_params(argc, argv);
	check_map(game, argv[1]);
	start_win(game);
	mlx_hook(game->win, 2, 1L << 0, press, game);
	mlx_hook(game->win, 3, 1L << 1, release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	close_game(game);
	free(game->mlx);
}
