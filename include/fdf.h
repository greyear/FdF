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
# include <limits.h>

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
	double	x;
	double	y;
	int		z;
	int		or_z;
	t_color	color;
}	t_iso;

typedef struct s_iso_mtx
{
	t_iso	**map;
	int		width;
	int		height;
}	t_iso_mtx;

typedef struct s_px
{
	int		x;
	int		y;
	int		z;
	t_color	color;
}	t_px;

typedef struct s_px_mtx
{
	t_px	**map;
	int		width;
	int		height;
}	t_px_mtx;

typedef struct s_extr
{
	double	b_x;
	double	s_x;
	double	b_y;
	double	s_y;
	int		b_z;
	int		s_z;
}	t_extr;

typedef struct s_line
{
	int		del_x;
	int		del_y;
	int		sign_x;
	int		sign_y;
	int		error;
}	t_line;

typedef struct s_draw
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_read		*read;
	double		zoom;
	double		mult;
	t_extr		ext;
	int			colorful;
	double		of_x;
	double		of_y;
	double		mv_x;
	double		mv_y;
	float		flat;
	double		alpha;
	double		beta;
	double		gamma;
	int			parallel;
}	t_draw;

typedef struct s_start
{
	int		fd;
	char	*line;
	t_read	*first;
	t_read	*last;
	char	**point_info;
	int		exp_len;
	int		arr_len;
	int		x;
	int		y;
	int		z;
	t_color	color;
}	t_start;

//Reading
t_read		*read_map(char *file_name);
char		**separate_line(t_start *start);
void		parse_line(t_start *start);

//Reading utils
t_read		*last_elem(t_read *stack);
t_read		*new_elem(int x, int y, int z, t_color color);
t_read		*add_to_back(t_read **old_last, t_read *new_last);
int			contains_comma(char *str);
int			array_len(char	**separate);

//Transforming to 2D
void		rotate_x(int *y, int *z, double alpha);
void		rotate_y(int *x, int *z, double beta);
void		rotate_z(int *x, int *y, double gamma);
t_iso_mtx	fill_iso_mtx(double angle, t_draw *pic);

//Colors
t_color		extract_rgba(int color, int len);
int			mix_rgba(int r, int g, int b, int a);
t_color		set_color_to_height(int z, int max_z, int min_z);
t_color		color_between(t_px start, t_px cur, t_px end);
int			is_colorful_input(t_iso_mtx matrix);
t_color		for_colorful_or_not(t_iso p, t_draw *pic);
int			color_len(char *str);
t_color		fake_color(void);
t_color		white_color(void);
int			is_fake(t_color c);

//Drawing
t_px_mtx	fill_px_mtx(t_iso_mtx iso_mtx, t_draw *pic);
void		put_px_mtx(mlx_image_t *image, t_px_mtx matrix);
void		draw_line(mlx_image_t *image, t_px a, t_px b);
t_extr		find_extremum(t_iso_mtx matrix);
double		find_zoom(t_extr extremum, int width, int height);
int			is_inside(int point_x, int point_y, int limit_x, int limit_y);
void		default_picture(t_draw *pic);
int			draw_picture(t_draw *pic);
void		pic_params(t_extr e, t_draw *pic);
void		refresh_picture(t_draw *pic);
void		delete_exit(t_draw *pic);
void		track_keys(mlx_key_data_t keydata, void *param);
void		track_scroll(double xdelta, double ydelta, void *param);

//Bonus functions
void		move(mlx_key_data_t keydata, t_draw	*pic);
void		zoom(double ydelta, t_draw	*pic);
void		rotate(mlx_key_data_t keydata, t_draw *pic);
void		flatten(mlx_key_data_t keydata, t_draw	*pic);
void		projection(mlx_key_data_t keydata, t_draw *pic);

//Cleaners
void		clean_read_map(t_read **stack);
void		clean_iso_map(t_iso ***map, int height);
void		clean_iso_mtx(t_iso_mtx *matrix);
void		clean_px_map(t_px ***map, int height);
void		clean_px_mtx(t_px_mtx *matrix);
void		clean_arr(char **arr);
void		clean_gnl(int fd);

//Checkers
void		check_rectangular(int y, int arr_len, t_start *start);
int			height_check(char *str);
int			color_check(char *str);

//Errors
void		args_error(void);
void		map_error(void);
void		error_opening(void);
void		input_data_error(t_start *start);

#endif
