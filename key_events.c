/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anespoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 14:24:34 by anespoul          #+#    #+#             */
/*   Updated: 2016/05/17 14:35:23 by anespoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				key_press(int key, t_env *e)
{
	if (key == ESC)
		exit(0);
	if (key == SNEAKY)
		e->m.sneaky = 1;
	if (key == JUMP)
		e->m.jump = 1;
	if (key == SPRINT)
		e->m.sprint = 1;
	if (key == UP)
		e->m.up = 1;
	if (key == LEFT)
		e->m.left = 1;
	if (key == RIGHT)
		e->m.right = 1;
	if (key == DOWN)
		e->m.down = 1;
	return (0);
}

int				key_release(int keycode, t_env *e)
{
	if (keycode == SNEAKY)
	{
		e->m.sneaky = 0;
		e->lvl = 50;
		e->mvspd = 0.05;
	}
	if (keycode == JUMP)
	{
		e->m.jump = 0;
		e->mvspd = 0.05;
	}
	if (keycode == SPRINT)
	{
		e->m.sprint = 0;
		e->mvspd = 0.05;
	}
	if (keycode == LEFT)
		e->m.left = 0;
	if (keycode == UP)
		e->m.up = 0;
	if (keycode == RIGHT)
		e->m.right = 0;
	if (keycode == DOWN)
		e->m.down = 0;
	return (0);
}

void			jump(t_env *e)
{
	if (e->m.jump == 0 && e->m.sneaky == 0)
	{
		if (e->lvl < 50)
			e->lvl += 35;
		if (e->j == 1)
			e->jx++;
		if (e->jx > 30 && e->lvl >= 50)
		{
			e->lvl = 50;
			e->j = 0;
			e->jx = 0;
		}
	}
	if (e->m.jump && e->jx == 0 && e->m.sneaky == 0)
	{
		e->mvspd = 0.15;
		if (e->lvl > -150)
			e->lvl -= 20;
		if (e->lvl <= -150)
		{
			e->mvspd = 0.05;
			e->m.jump = 0;
			e->j = 1;
		}
	}
}

int				ft_exit(t_env *e)
{
	exit(0);
}

int				loop_hook(t_env *e)
{
	jump(e);
	side_move(e);
	up_and_down(e);
	if (e->m.sneaky)
	{
		e->lvl = 150;
		e->mvspd = 0.01;
	}
	if (e->m.sprint && !e->m.sneaky)
	{
		e->mvspd = 0.1;
		if (e->m.left || e->m.right)
			e->mvspd = 0.05;
	}
	return (1);
}
