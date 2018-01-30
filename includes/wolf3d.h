/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhill <dhill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:03:33 by dhill             #+#    #+#             */
/*   Updated: 2018/01/29 00:57:09 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <libft.h>
# include <mlx.h>

# define FRAMETIME 1.0
# define R_CHANGE(x, a, b, min, max)	(((b - a) * (x - min)/(max - min)) + a)
# define RAD(x)							(x * PI / 180)

typedef	unsigned	t_color;

typedef struct		s_screen
{
	void			*mlx;
	void			*win;
	void			*pic;
	int				bits;
	int				s_line;
	int				endian;
	int				*canvas;
	int				win_height;
	int				win_width;
}					t_screen;

typedef struct		s_ind
{
	int				x;
	int				y;
}					t_ind;

typedef struct		s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct		s_texture
{
	void			*pic;
	int				*canvas;
	int				x;
	int				y;
	int				bits;
	int				s_line;
	int				endian;
}					t_exture;

typedef	struct		s_textures
{
	t_exture		n_wall;
	t_exture		s_wall;
	t_exture		e_wall;
	t_exture		w_wall;
	t_exture		floor;
	t_exture		ceiling;
	t_exture		blank;
}					t_extures;

typedef struct		s_variables
{
	void			*win_ptr;
	void			*img_ptr;
	void			*mlx_ptr;
	char			*img_addr;
	int				endian;
}					t_mlx_var;

typedef struct		s_flags
{
	int				l;
	int				r;
	int				f;
	int				b;
}					t_flags;

typedef struct		s_room
{
	char			**room;
	char			*name;
}					t_room;

typedef struct		s_ray
{
	int				x;
	double			camera_x;
	t_coord			dir;
	t_ind			map;
	t_coord			delta_dist;
	t_coord			side_dist;
	t_ind			step;
	int				hit;
	int				side;
}					t_ray;

typedef struct		s_screen_draw
{
	t_exture		texture;
	t_coord			floor_wall;
	t_ray			ray;
	double			dist_wall;
	double			perp_wall_dist;
	int				line_height;
	double			wall_x;
	int				tex_x;
	int				x;
	int				y;
}					t_draw;

typedef struct		s_wolf
{
	t_coord			pos;
	t_coord			dir;
	t_coord			strafe;
	t_coord			plane;
	double			move_speed;
	double			rot_speed;
	int				w;
	int				h;
	int				exit;
	int				win;
	int				draw;
	int				lclicked;
	char			**map;
	t_room			world[6];
	int				it;
	t_screen		screen;
	t_flags			flags;
	int				lturn;
	int				rturn;
	int				mid;
	int				last_mp;
	t_extures		textures;
	int				draw_start;
	int				draw_end;
	unsigned		*buf;
	char			clicked_on;
}					t_wolf;

char				**parse(char *file);
void				ft_error(char *str);
t_screen			init_screen(int win_width, int win_height, char *name);
void				paint(t_screen *screen, int x, int y, t_color color);
t_color				ft_rgb(int r, int g, int b);
void				init_img(t_screen *screen);
void				draw_img(t_screen *screen);
void				screen_img(t_screen *screen);
t_coord				init_coord(double x, double y);
void				redraw(t_wolf *wolf);

t_ray				init_ray(t_wolf *wolf, int x, int w);
double				dda(t_ray *ray, t_wolf *wolf);
double				raycast(t_ray *ray, t_wolf *wolf);
void				set_screen(t_wolf *wolf);
void				set_line_buf(t_wolf *wolf, int tex_x,
						int line_height, t_exture t);
void				set_fc_buf(t_wolf *wolf, t_draw *d);
void				draw_line(t_wolf *wolf, int x);

t_ind				init_pair(int x, int y);
t_coord				pos_of(char **arr, int val);
t_wolf				init_wolf(void);

void				move(t_wolf *wolf);
void				jump(t_wolf *wolf);

int					mouse_click_event(int button, int x, int y, t_wolf *wolf);
int					key_up_event(int keycode, t_wolf *wolf);
int					close_window(t_wolf *wolf);
int					motion_event(int x, int y, t_wolf *wolf);
int					key_down_event(int keycode, t_wolf *wolf);

#endif
