/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anespoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 14:14:18 by anespoul          #+#    #+#             */
/*   Updated: 2016/05/17 12:33:11 by anespoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				move_c(int x, int y, t_env *e)
{
	double			olddirx;
	double			oldplanex;
	double			c;

	olddirx = e->dirx;
	oldplanex = e->planex;
	c = 0.01 * (ABS(x - e->mouse));
	if (x > e->mouse)
		c = -c;
	if (x == e->mouse)
	{
		c = 0.05;
		if (x > 0)
			c = -c;
	}
	e->dirx = e->dirx * cos(c) - e->diry * sin(c);
	e->diry = olddirx * sin(c) + e->diry * cos(c);
	e->planex = e->planex * cos(c) - e->planey * sin(c);
	e->planey = oldplanex * sin(c) + e->planey * cos(c);
	e->mouse = x;
	return (1);
}

void			side_move(t_env *e)
{
	if (e->m.left)
	{
		if (!g_wmap[(int)(e->posx - e->diry * e->mvspd)][(int)(e->posy)])
			e->posx -= e->diry * e->mvspd / 2;
		if (!g_wmap[(int)(e->posx)][(int)(e->posy + e->dirx * e->mvspd)])
			e->posy += e->dirx * e->mvspd / 2;
	}
	if (e->m.right)
	{
		if (g_wmap[(int)(e->posx + e->diry * e->mvspd)][(int)(e->posy)] == 0)
			e->posx += e->diry * e->mvspd / 2;
		if (g_wmap[(int)(e->posx)][(int)(e->posy - e->dirx * e->mvspd)] == 0)
			e->posy -= e->dirx * e->mvspd / 2;
	}
}

void			up_and_down(t_env *e)
{
	if (e->m.up)
	{
		if (!g_wmap[(int)(e->posx + e->dirx * e->mvspd)][(int)(e->posy)])
			e->posx += e->dirx * e->mvspd;
		if (!g_wmap[(int)(e->posx)][(int)(e->posy + e->diry * e->mvspd)])
			e->posy += e->diry * e->mvspd;
	}
	if (e->m.down)
	{
		if (g_wmap[(int)(e->posx - e->dirx * e->mvspd)][(int)(e->posy)] == 0)
			e->posx -= e->dirx * e->mvspd;
		if (g_wmap[(int)(e->posx)][(int)(e->posy - e->diry * e->mvspd)] == 0)
			e->posy -= e->diry * e->mvspd;
	}
}
