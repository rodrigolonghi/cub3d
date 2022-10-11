/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:34:40 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/10 21:22:35 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	start_win(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, HEIGHT, WIDTH, "cub3D");
	// load_image(game);
	// put_images(game);
}

void	start_game(t_game *game, int argc, char *argv[])
{
	check_params(argc, argv);
	check_map(game, argv[1]);
	start_win(game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	// mlx_expose_hook(game->win, put_images, game);
	mlx_loop(game->mlx);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	close_game(game);
	free(game->mlx);
}
