/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xdm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:50:28 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/08 11:03:50 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_xdm(t_all *vars, t_pos *xdm, int i)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (xdm[i - a].x == xdm[i].x && xdm[i - a].y == xdm[i].y)
		a++;
	while (xdm[i + b].x == xdm[i].x && xdm[i + b].y == xdm[i].y)
		b++;
	return (a + b - 1);
}
