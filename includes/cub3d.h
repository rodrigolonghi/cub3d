/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:04:10 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/11/11 18:55:26 by rfelipe-         ###   ########.fr       */
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
	int		bits_per_pixel;
	int		endian;
	int		line_length;
	char	*data;
	void	*ptr;
}	t_data;

typedef struct s_texture
{
	int		height;
	int		width;
	char	*addr;
	t_data	img;
}	t_texture;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_player
{
	t_vec	player_dir;
	t_vec	player_pos;
	t_vec	strafe_vel;
	t_vec	velocity;
	double	movement_speed;
	double	rotation_speed;
}	t_player;

typedef struct s_dda
{
	int			hit_side;
	t_vec		camera_pixel;
	t_vec		camera_plane;
	t_vec		hit_pos;
	t_vec		ray_dir;
	double		delta_dist_x;
	double		delta_dist_y;
	double		dist_to_side_x;
	double		dist_to_side_y;
	double		multiplier;
	double		perp_dist;
	double		step_x;
	double		step_y;
	double		wall_end_y;
	double		wall_height;
	double		wall_start_y;
}	t_dda;

typedef struct s_file_data
{
	t_map		map;
	t_color		ceilling;
	t_color		floor;
	t_texture	*texture;
}	t_file_data;

typedef struct s_game
{
	int			error;
	int			rotation;
	void		*mlx;
	void		*win;
	t_dda		dda;
	t_vec		map_pos;
	double		dist_wall;
	double		x_walk;
	double		y_walk;
	t_player	p;
	t_file_data	file;
}	t_game;

int		check_movement(t_game *g, int x, int y);
int		close_game(t_game *game);
int		encode_rgb(t_color color);
int		is_valid_cell(t_game *game, int rows, int cols);
int		is_valid_end(t_game *game);
int		map_started(char *line);
int		open_fd(char *file);
int		press(int key, t_game *game);
int		release(int key, t_game *game);
int		render(t_game *game);
void	calculate(t_game *game);
void	calculate_current_ray(t_game *game, int i);
void	calculate_dda_variables(t_game *game);
void	check_edges(t_game *game, char cell);
void	check_map(t_game *game, char *map);
void	check_params(t_game *game, int argc, char *argv[]);
void	check_surroundings(t_game *game, int rows, int cols);
void	fill_background(t_game *game);
void	get_delta_dist(t_game *game);
void	get_dist_to_side(t_game *game);
void	go_down(t_game *game);
void	go_up(t_game *game);
void	read_until_end(int fd);
void	refresh_player(t_game *game);
void	save_colors(t_game *g, char id, char *color);
void	save_e_w_texture(t_game *game, char id, char *path);
void	save_n_s_texture(t_game *game, char id, char *path);
void	save_player(t_game *g, int rows, int cols);
void	start_game(t_game *game, int argc, char *argv[]);
void	throw_error(char *e, t_game *game);
void	validate_player(t_game *game);
t_vec	create_vector(double x, double y);
t_vec	vector_add(t_vec a, t_vec b);
t_vec	vector_mul(t_vec a, t_vec b);
t_vec	vector_mul_scal(t_vec a, double b);
t_vec	vector_rotation(t_vec vec, double degree, int rotation);
t_color	create_color(double r, double g, double b);

#endif
