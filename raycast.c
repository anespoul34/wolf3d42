/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anespoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 17:07:06 by anespoul          #+#    #+#             */
/*   Updated: 2016/05/17 12:28:59 by anespoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		initray(t_env *e, int x)
{
	e->camx = 2 * x / (double)(WIDTH) - 1;
	e->rposx = e->posx;
	e->rposy = e->posy;
	e->rdirx = e->dirx + e->planex * e->camx;
	e->rdiry = e->diry + e->planey * e->camx;
	e->mapx = (int)(e->rposx);
	e->mapy = (int)(e->rposy);
	e->deltadistx = sqrt(1 + (e->rdiry * e->rdiry) / (e->rdirx * e->rdirx));
	e->deltadisty = sqrt(1 + (e->rdirx * e->rdirx) / (e->rdiry * e->rdiry));
	e->hit = 0;
}

static void		raydir(t_env *e)
{
	if (e->rdirx < 0)
	{
		e->stepx = -1;
		e->sidedistx = (e->rposx - e->mapx) * e->deltadistx;
	}
	else
	{
		e->stepx = 1;
		e->sidedistx = (e->mapx + 1.0 - e->rposx) * e->deltadistx;
	}
	if (e->rdiry < 0)
	{
		e->stepy = -1;
		e->sidedisty = (e->rposy - e->mapy) * e->deltadisty;
	}
	else
	{
		e->stepy = 1;
		e->sidedisty = (e->mapy + 1.0 - e->rposy) * e->deltadisty;
	}
}

static void		dda(t_env *e)
{
	while (e->hit == 0)
	{
		if (e->sidedistx < e->sidedisty)
		{
			e->sidedistx += e->deltadistx;
			e->mapx += e->stepx;
			e->side = 0;
		}
		else
		{
			e->sidedisty += e->deltadisty;
			e->mapy += e->stepy;
			e->side = 1;
		}
		if (g_wmap[e->mapx][e->mapy] > 0)
			e->hit = 1;
	}
}

static void		compute(t_env *e)
{
	if (e->side == 0)
		e->perpwalldist = (e->mapx - e->rposx + (1 - e->stepx) / 2) / e->rdirx;
	else
		e->perpwalldist = (e->mapy - e->rposy + (1 - e->stepy) / 2) / e->rdiry;
	e->lineheight = (int)(WIDTH / e->perpwalldist);
	e->drawstart = -e->lineheight / 2 + WIDTH / 2;
	if (e->drawstart < 0)
		e->drawstart = 0;
	e->drawend = e->lineheight / 2 + WIDTH / 2;
	if (e->drawend >= WIDTH)
		e->drawend = WIDTH - 1;
}

int				ft_map(t_env *e)
{
	int		x;

	if (e->img != NULL)
	{
		mlx_destroy_image(e->mlx, e->img_ptr);
		e->img = NULL;
	}
	e->img_ptr = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->img = mlx_get_data_addr(e->img_ptr, &(e->bpp), &(e->sl), &(e->end));
	x = 0;
	while (x < WIDTH)
	{
		initray(e, x);
		raydir(e);
		dda(e);
		compute(e);
		draw_line(x, e);
		x++;
	}
	loop_hook(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img_ptr, 0, 0);
	return (0);
}
