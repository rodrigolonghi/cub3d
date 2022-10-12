/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:30:28 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/12 15:37:40 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate(t_game *game)
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
