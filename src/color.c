/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:21:31 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/12 15:33:18 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render(t_game *game)
{
	int	x;
	int	y;

	y = HEIGHT - 1;
	while (y >= 1)
	{
		x = 1;
		while (x < WIDTH - 1)
		{
			mlx_pixel_put(game->mlx, game->win, x, HEIGHT - y,
				game->map.pixel_map[x][y]);
			x++;
		}
		y--;
	}
	return (0);
}

int	encode_rgb(t_color color)
{
	return ((int)(color.r) << 16 | (int)(color.g) << 8 | (int)(color.b));
}

t_color	create_color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}
