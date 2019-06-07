/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anespoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 12:36:26 by anespoul          #+#    #+#             */
/*   Updated: 2016/05/05 18:22:05 by anespoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_for_x_y(int x, int y, t_env *e)
{
	if (x <= 0 || x >= WIDTH)
		return (0);
	if (y <= 0 || y >= HEIGHT)
		return (0);
	if (x * 4 + y * e->sl > WIDTH * 4 + HEIGHT * e->sl)
		return (0);
	return (1);
}

void	ft_clean(t_env *e)
{
	int p;

	p = -1;
	while (++p < WIDTH * 4 + HEIGHT * e->sl)
		e->img[p] = 0;
}
