/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:34:40 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/14 22:32:25 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	initiate(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->camera_plane = create_vector(0.66, 0);
}

static void	start_win(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	// load_image(game);
	calculate(game);
	render(game);
}

void	start_game(t_game *game, int argc, char *argv[])
{
	initiate(game);
	check_params(argc, argv);
	check_map(game, argv[1]);
	start_win(game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	// mlx_expose_hook(game->win, render, game);
	mlx_loop(game->mlx);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	close_game(game);
	free(game->mlx);
}
