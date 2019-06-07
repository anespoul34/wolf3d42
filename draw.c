/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anespoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 17:33:35 by anespoul          #+#    #+#             */
/*   Updated: 2016/05/17 12:32:13 by anespoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_color(t_env *e, int x, int y, unsigned int c)
{
	int		p;

	p = x * 4 + y * e->sl;
	if (check_for_x_y(x, y, e) && !e->img[p])
	{
		e->img[p] = c & 0xff;
		e->img[p + 1] = (c >> 8) & 0xff;
		e->img[p + 2] = (c >> 16) & 0xff;
	}
}

void	draw_line(int x, t_env *e)
{
	t_point			p;
	unsigned int	c;

	c = 0x996633;
	if (e->side == 0 && e->stepx == -1)
		c = 0x00ff66;
	if (e->side == 0 && e->stepx == 1)
		c = 0xff3333;
	if (e->side == 1 && e->stepy == -1)
		c = 0xffff33;
	p.x = x;
	p.y = 0;
	while (p.y++ < e->drawstart - e->lvl)
		draw_color(e, p.x, p.y, 0x33ffff);
	draw_color(e, p.x, p.y, 0x000000);
	while (p.y++ < e->drawend - e->lvl)
		draw_color(e, p.x, p.y, c);
	draw_color(e, p.x, p.y, 0x000000);
	while (p.y++ < HEIGHT)
		draw_color(e, p.x, p.y, 0xffffff);
}
