/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:16:05 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/04 15:56:24 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define _GNU_SOURCE

# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h> //TODO: abs??
# include <limits.h>
# include <time.h> //TODO: measures

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

typedef struct s_read
{
	int				x;
	int				y;
	int				z;
	t_color			color;
	struct s_read	*next;
}	t_read;

typedef struct s_iso
{
	double			x;
	double			y;
	int				z;
	t_color			color;
}	t_iso;

typedef struct s_iso_matrix
{
	t_iso		**map;
	int			width;
	int			height;
}	t_iso_matrix;

typedef struct s_px
{
	int				x;
	int				y;
	int				z;
	t_color			color;
}	t_px;

typedef struct s_px_matrix
{
	t_px		**map;
	int			width;
	int			height;
}	t_px_matrix;

typedef struct s_extremum
{
	double	max_x;
	double	min_x;
	double	max_y;
	double	min_y;
	int		max_z;
	int		min_z;
}	t_extremum;

typedef struct s_draw
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_read		*read;
	double		zoom;
	double		move_x;
	double		move_y;
	float		flat; //can it be double?
	double		alpha;
	double		beta;
	double		gamma;
}	t_draw;

//Reading
t_read			*read_map(char *file_name);

//Utils
t_read			*last_elem(t_read *stack);
t_read			*add_to_last(t_read **old_last, int x, int y, int z, t_color color);
int				contains_comma(char *str);
int				is_nl(char *str);
int				array_len(char	**separate);

//Transforming to 2D
t_iso_matrix	to_iso_matrix(t_read *stack, double angle, t_draw *pic);

//Colors
int				mix_rgba(int r, int g, int b, int a);
t_color			fake_color(void);
t_color			white_color(void);
int				is_fake(t_color c);
t_color			extract_rgba(int color, int len);
t_color			set_color_to_height(int z, int max_z, int min_z);
t_color			color_between(t_px start, t_px cur, t_px end);
int				color_len(char *str);

//Drawing
t_px_matrix		to_px_matrix(mlx_image_t *image, t_iso_matrix iso_matrix, t_draw *pic);
void			put_px_matrix(mlx_image_t *image, t_px_matrix matrix);
void			draw_line(mlx_image_t *image, t_px a, t_px b);
t_extremum		find_extremum(t_iso_matrix matrix); // TODO: static
double			find_zoom(t_extremum extremum, int width, int height);
int				is_colorful_input(t_iso_matrix matrix);
int				is_inside(int point_x, int point_y, int limit_x, int limit_y);
void			default_picture(t_draw *pic);
int				draw_picture(mlx_t *mlx, t_read *read, t_draw *pic);
void			refresh_picture(t_draw *pic);
void			delete_exit(t_draw *pic);
void			track_keys(mlx_key_data_t keydata, void *param);
void			track_scroll(double xdelta, double ydelta, void *param);

//Bonus functions
void			move(mlx_key_data_t keydata, t_draw	*pic);
void			zoom(double ydelta, t_draw	*pic);
void			rotate(mlx_key_data_t keydata, t_draw *pic);
void			flatten(mlx_key_data_t keydata, t_draw	*pic);

//Cleaners
void			clean_read_map(t_read **stack);
void			clean_iso_map(t_iso ***map, int height);
void			clean_iso_matrix(t_iso_matrix *matrix);
void			clean_px_matrix(t_px_matrix *matrix);
void			clean_arr(char **arr);
void			clean_gnl(int fd);

//Checkers
int				height_check(char *str);
int				color_check(char *str);

#endif
