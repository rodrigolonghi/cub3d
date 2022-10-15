/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:04:10 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/10/15 01:32:02 by acarneir         ###   ########.fr       */
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
# define WIDTH			960
# define HEIGHT			600

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

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
	t_vec		player_pos;
	t_vec		player_dir;
	t_vec		map_pos;
	t_vec		hit_pos;
	t_vec		camera_plane;
	t_vec		camera_pixel;
	double		delta_dist_x;
	double		delta_dist_y;
	double		dist_to_side_x;
	double		dist_to_side_y;
	double		step_x;
	double		step_y;
	double		perp_dist;
	t_vec		ray_dir;
	double		multiplier;
	int			hit_side;
	int			*characters;
}	t_game;

void	start_game(t_game *game, int argc, char *argv[]);
int		close_game(t_game *game);
int		key_hook(int key, void *param);
void	throw_error(char *e, t_game *game);
void	check_params(int argc, char *argv[]);
int		open_fd(char *file);
void	check_map(t_game *game, char *map);
t_color	create_color(double r, double g, double b);
int		encode_rgb(t_color color);
int		render(t_game *game);
void	calculate(t_game *game);
t_vec	create_vector(double x, double y);
t_vec	vector_add(t_vec a, t_vec b);
t_vec	vector_mul_scal(t_vec a, double b);

#endif
