/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:50:28 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/08 11:03:50 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	ft_mymlx_pixelput(t_all *vars, t_data *data)
{
	char	*dst;
	int	x;
	int	y;
	double	px;
	double	py;


	x = -1;
	while (++x < vars->rsl.w)
	{
		y = -1;
		while (++y < vars->rsl.h)
		{
			dst = data->addr + (y * data->ll + x * (data->bpp / 8));
			px = (double)(x / ((double)vars->rsl.w / 64));
			py = (double)(y / ((double)vars->rsl.h / 64));
			px = (int)px % 64;
			py = (int)py % 64;
			*(unsigned int*)dst = 
				ft_get_xpm_pixel(&vars->spr.data[3],px, py);
		}
	}
}*/

int	ft_myxpm_pixelput(t_all *vars, int e, t_pos *xdm, t_pos *pos)
{
	int	color;
	int	a;
	int	b;
	int	px;
	int	py;

	a = 0;
	while (xdm[pos->x - a].x == xdm[pos->x].x &&
			xdm[pos->x - a].y == xdm[pos->x].y)
		a++;
	a--;
	b = pos->y - e;
	/*printf("a = %d, b = %d , xdm = %d, rsl.h-2e = %d \n", a, b, ft_xdm(vars, xdm, pos->x), (vars->rsl.h - (2 * e)));*/
	px = ft_get_pxy(a, ft_xdm(vars, xdm, pos->x));
	/*px = ft_get_pxy(a, (vars->rsl.h - (2 * e)) * (vars->rsl.w / vars->rsl.h));*/
	py = ft_get_pxy(b, vars->rsl.h - (2 * e));
	/*printf("px = %d, py = %d \n", px, py);*/
	color = ft_get_xpm_pixel(&vars->spr.data[vars->wallface[pos->x]], px, py);
	return (color);
}

int	ft_get_pxy(int xy, int wh)
{
	double	pxy;

	pxy = (double)(xy / ((double)wh / 64));
	pxy = (int)pxy % 64;
	return (pxy);
}

int	ft_get_xpm_pixel(t_data *data, int x, int y)
{
	int	color;

	color = *((int*)data->addr + (x + y * 64));
	return (color);
}
