/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anespoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 11:56:25 by anespoul          #+#    #+#             */
/*   Updated: 2016/05/17 14:41:12 by anespoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "./libft/includes/libft.h"
# include "minilibx/mlx.h"
# include <math.h>
# include <sys/time.h>

# define WIDTH		1280
# define HEIGHT		900
# define ESC		53
# define UP			13
# define DOWN		1
# define RIGHT		2
# define LEFT		0
# define SPRINT		257
# define SNEAKY		256
# define ACTION		14
# define MENU		48
# define JUMP		49
# define ABS(x)		((x) < 0 ? -(x) : (x))

# define MAPWIDTH	24
# define MAPHEIGHT	24

static int		g_wmap[MAPWIDTH][MAPHEIGHT] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 2, 0, 2, 2, 2, 2, 2, 0, 2, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 2, 0, 2, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
	{1, 0, 2, 2, 2, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 2, 2, 2, 0, 0, 2, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 2, 0, 0, 2, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 2, 0, 0, 2, 0, 2, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 2, 2, 1, 0, 0, 0, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
	{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef	struct		s_move
{
	int				sprint;
	int				sneaky;
	int				up;
	int				down;
	int				left;
	int				right;
	int				jump;
}					t_move;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img_ptr;
	char			*img;
	int				**tab;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	int				bpp;
	int				end;
	int				sl;
	double			camx;
	double			rposx;
	double			rposy;
	double			rdirx;
	double			rdiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				lvl;
	int				drawstart;
	int				drawend;
	int				mouse;
	double			mvspd;
	double			rtspd;
	char			**content;
	int				j;
	int				jx;
	struct s_color	c;
	struct s_move	m;
}					t_env;

typedef struct		s_coord
{
	int				x;
	int				y;
	int				z;
	struct s_color	c;
}					t_coord;

int					ft_exit(t_env *e);
void				up_and_down(t_env *e);
void				side_move(t_env *e);
int					move_c(int x, int y, t_env *e);
int					loop_hook(t_env *e);
static void			turn(t_env *e, char dir);
int					key_release(int keycode, t_env *e);
int					key_press(int keycode, t_env *e);
int					expose_hook(t_env *e);
int					key_events(int key, t_env *e);
int					check_for_x_y(int x, int y, t_env *e);
void				draw_line(int x, t_env *e);
void				handle_map(t_env *e);
void				init_env(t_env *e);
void				get_point_color(t_env *e, t_coord *p);
int					ft_map(t_env *e);
void				error(int i);
void				ft_clean(t_env *e);

#endif
