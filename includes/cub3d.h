/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:04:10 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/12 15:34:36 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// INCLUDES
# include "../libft/includes/libft.h"
# include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# define LEFT			0x61
# define RIGHT			0x64
# define DOWN			0x73
# define UP				0x77
# define ARROW_LEFT		0xff51
# define ARROW_RIGHT	0xff53
# define ESC			0xff1b
# define WIDTH			800
# define HEIGHT			450

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_map
{
	int		cols;
	int		rows;
	int		pixel_map[WIDTH][HEIGHT];
	char	**coordinates;
}	t_map;

typedef struct s_sprite
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}	t_sprite;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_color		ceilling;
	t_color		floor;
	t_sprite	no;
	t_sprite	so;
	t_sprite	we;
	t_sprite	ea;
	t_map		map;
	t_pos		player_pos;
}	t_game;

void	start_game(t_game *game, int argc, char *argv[]);
int		close_game(t_game *game);
int		key_hook(int key, void *param);
void	throw_error(char *e);
void	check_params(int argc, char *argv[]);
void	check_map(t_game *game, char *map);
t_color	create_color(double r, double g, double b);
int		encode_rgb(t_color color);
int		render(t_game *game);
void	calculate(t_game *game);

#endif
