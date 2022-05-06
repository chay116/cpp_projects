/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <chalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:13:58 by chalim            #+#    #+#             */
/*   Updated: 2022/03/17 19:36:46 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdbool.h>
# include "get_next_line.h"
# include "../Libft/libft.h"
# include "../mlx/mlx.h"
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <errno.h>

# define RAY_MAX 2
# define ERROR -1
# define ERR -1
# define GOOD 1
# define PI 3.1415926

# ifndef _XSIZE
#  define _XSIZE 1080
# endif

# ifndef _YSIZE
#  define _YSIZE 720
# endif

# ifndef WIN
#  define WIN "miniRT"
# endif

# define RESET 48
# define R 18
# define G 19
# define B 20

# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define THETA_UP 126
# define THETA_DOWN 125
# define PSI_LEFT 123
# define PSI_RIGHT 124

# define ESC 53
# define KEYPRESS 2
# define KEYREL	3

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
	bool			in;
}					t_vec3;

typedef struct		s_color
{
	double			red;
	double			green;
	double			blue;
}					t_color;

typedef struct		s_sphere
{
	double			a;
	double			b;
	double			c;
	int				type;
	t_vec3			pos;
	t_vec3			vec;
	double			dia;
	double			height;
	t_color			color;
	struct s_sphere	*next;
}					t_sphere;

typedef struct		s_light
{
	t_vec3			pos;
	double			power;
	t_color			color;
	struct s_light	*next;
}					t_light;

typedef struct		s_sum
{
	t_vec3			*ray_pos;
	t_vec3			*norm;
	t_sphere		*cy;
	t_vec3			*ray;
	double			an[6];
	double			answer;
	int				number;
}					t_sum;

typedef struct		s_result
{
	t_vec3			norm;
	t_vec3			pos;
	t_sphere		*target;
}					t_result;

typedef struct		s_data
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				res_x;
	int				res_y;
	bool			amb;
	double			a_power;
	t_color			a_color;
	bool			camera;
	t_vec3			c_pos;
	t_vec3			c_vec;
	double			c_fov;
	double			c_size;
	double			c_x;
	double			zoom;
	int				endian;
	int				left;
	int				right;
	int				up;
	int				down;
	int				psi_left;
	int				psi_right;
	int				theta_up;
	int				theta_down;
	bool			error;
	int				pos;
	t_sphere		*sphere;
	int				is_light;
	t_light			*light;
	t_vec3			rx;
	t_vec3			ry;
	t_vec3			ray;
	double			theta;
	double			psi;
	double			omega;
	double			r_unit;
	t_result		result;
}					t_data;

int					mlx_mouse_operation(int button, int x, int y, t_data *data);
int					ft_key_press(int keycode, t_data *data);
int					ft_key_release(int keycode, t_data *data);
int					mlx_key_operation(t_data *data);
int					mlx_color(t_data *data);
int					rt_reader(char *line, t_data *data);
int					put_color(t_color *color, char *line);
int					put_vector(t_vec3 *vec, char *line);
int					put_pos(t_vec3 *vec, char *line);
int					atoi_int(char **str);
int					atoi_double(char **str, double *num);
void				set_camera(char **words, t_data *data);
void				set_ambient(char **words, t_data *data);
void				set_light(char **words, t_data *data);
void				set_sphere(char **words, t_data *data);
double				inner_vec3(t_vec3 *vec1, t_vec3 *vec2);
void				outer_vec3(t_vec3 *vec1, t_vec3 *vec2, t_vec3 *new_vec3);
double				size_vec3(t_vec3 *vec);
void				cal_vec_vec(t_vec3 *vec1, char operator, \
					t_vec3 *vec2, t_vec3 *res);
void				cal_vec_num(t_vec3 *vec1, char operator, \
					double num, t_vec3 *res);
void				norm_vec(t_vec3 *vec);
int					mlx_draw(t_data *data);
double				hit_sphere(t_vec3 *ray_pos, t_sphere *sphere, \
					t_vec3 *norm, t_vec3 *ray);
void				cal_col_col(t_color *vec1, char operator, \
					t_color *vec2, t_color *res);
void				cal_col_num(t_color *vec1, char operator, \
					double num, t_color *res);
void				get_rxry(t_data *data);
void				insert_color(t_color *color, t_data *data);
double				find_closest(t_data *data, t_vec3 *ray, t_vec3 \
					*pos, t_result *result);
double				hit_cylinder(t_vec3 *ray_pos, t_sphere *sphere, \
								t_vec3 *norm, t_vec3 *ray);
void				get_rxry(t_data *data);
void				get_theta_psi(t_data *data);
int					check(t_data *data);
void				find_end_object(t_data *data, t_sphere *new);
void				set_sphere(char **words, t_data *data);
void				set_plane(char **words, t_data *data);
void				set_cylinder(char **words, t_data *data);
void				set_ending(void);
double				hit_upcircle(t_sum *s);
double				hit_downcircle(t_sum *s);
double				hit_cy(t_sum *s);

#endif
