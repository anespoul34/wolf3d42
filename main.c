/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anespoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 13:34:26 by anespoul          #+#    #+#             */
/*   Updated: 2016/05/17 14:36:04 by anespoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_env(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		return ;
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "Wolf3D_42");
	e->bpp = 8;
	e->end = 0;
	e->sl = WIDTH;
	e->posx = 22;
	e->posy = 12;
	e->dirx = -1;
	e->diry = 0;
	e->planex = 0;
	e->planey = 0.66;
	e->img_ptr = NULL;
	e->img = NULL;
	e->mvspd = 0.05;
	e->rtspd = 0.0003;
	e->lvl = 50;
	e->j = 0;
	e->jx = 0;
	e->mouse = WIDTH / 2;
}

int		main(int ac, char **av)
{
	t_env	*e;

	e = (t_env *)malloc(sizeof(t_env));
	init_env(e);
	mlx_loop_hook(e->mlx, ft_map, e);
	mlx_hook(e->win, 17, (1L << 17), ft_exit, e);
	mlx_hook(e->win, 2, (1L << 0), key_press, e);
	mlx_hook(e->win, 3, (1L << 1), key_release, e);
	mlx_hook(e->win, 6, (1L << 6), move_c, e);
	mlx_loop(e->mlx);
	return (0);
}
