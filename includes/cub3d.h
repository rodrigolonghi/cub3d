/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:04:10 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/08 21:07:01 by acarneir         ###   ########.fr       */
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
# define TRUE			1
# define FALSE			0
# define PRESS			0
# define RELEASE		1
# define IMG_SIZE		60

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

typedef struct s_data
{
	void	*ptr;
	char	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;


typedef struct s_sprite
{
	t_data	img;
	char	*addr;
	int		width;
	int		height;
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
	double		x_walk;
	double		y_walk;
	int			rotation;
	double		movement_speed;
	double		rotation_speed;
	t_vec		velocity;
	t_vec		strafe_vel;
	char		player_orient;
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
	double		dist_wall;
	double		wall_height;
	double		wall_start_y;
	double		wall_end_y;
}	t_game;

void	start_game(t_game *game, int argc, char *argv[]);
int		close_game(t_game *game);
void	throw_error(char *e, t_game *game);
void	check_params(t_game *game, int argc, char *argv[]);
int		open_fd(char *file);
void	check_map(t_game *game, char *map);
t_color	create_color(double r, double g, double b);
int		encode_rgb(t_color color);
int		render(t_game *game);
void	calculate(t_game *game);
t_vec	create_vector(double x, double y);
t_vec	vector_add(t_vec a, t_vec b);
t_vec	vector_mul_scal(t_vec a, double b);
int		check_movement(t_game *g, int x, int y);
void	go_up(t_game *game);
void	go_down(t_game *game);
void	refresh_player(t_game *game);
int		press(int key, t_game *game);
int		release(int key, t_game *game);
t_vec	vector_rotation(t_vec vec, double degree, int rotation);
t_vec	vector_mul(t_vec a, t_vec b);

#endif
