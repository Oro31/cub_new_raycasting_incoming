/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hor_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 07:46:41 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/06 08:42:09 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_ne_hor_inte(t_all *vars, float angle, t_pos *xdm, int i)
{
	double	x;
	double	y;
	double	tmp;
	double	len;
	double	a;

	a = tan(angle);
	if (a < 0)
		a = a * -1;
	x = (double)((vars->map.cam.posx + 1) * 64);
	y = (double)((vars->map.cam.posy * 64) + 32 - (32 / a));
        ft_check_maplimites(vars, &x, &y, 'e');
	while (vars->map.box[(int)(y / 64)][(int)(x / 64)] == '0')
	{
		x = x + 64;
		y = y - (64 / a);
		ft_check_maplimites(vars, &x, &y, 'e');
	}
	xdm[i].y = (int)(y / 64);
	xdm[i].x = (int)(x / 64);
	tmp = pow(((double)vars->map.cam.posx * 64) + 32 - x, 2) +
		pow(((double)vars->map.cam.posy * 64) + 32 - y, 2);
	len = sqrt(tmp);
	return (len);
}

double	ft_nw_hor_inte(t_all *vars, float angle, t_pos *xdm, int i)
{
	double	x;
	double	y;
	double	tmp;
	double	len;
	double	a;

	a = tan(angle);
	if (a < 0)
		a = a * -1;
	x = (double)(vars->map.cam.posx * 64);
	y = (double)((vars->map.cam.posy * 64) + 32 - (32 / a));
	ft_check_maplimites(vars, &x, &y, 'w');
	while (vars->map.box[(int)(y / 64)][(int)(x / 64) - 1] == '0')
	{
		x = x - 64;
		y = y - (64 / a);
		ft_check_maplimites(vars, &x, &y, 'w');
	}
	xdm[i].y = (int)(y / 64);
	xdm[i].x = (int)(x / 64);
	tmp = pow(((double)vars->map.cam.posx * 64) + 32 - x, 2) +
		pow(((double)vars->map.cam.posy * 64) + 32 - y, 2);
	len = sqrt(tmp);
	return (len);
}

double	ft_sw_hor_inte(t_all *vars, float angle, t_pos *xdm, int i)
{
	double	x;
	double	y;
	double	tmp;
	double	len;
	double	a;

	a = tan(angle);
	if (a < 0)
		a = a * -1;
	x = (double)(vars->map.cam.posx * 64);
	y = (double)((vars->map.cam.posy * 64) + 32 + (32 / a));
	ft_check_maplimites(vars, &x, &y, 'w');
	while (vars->map.box[(int)(y / 64)][(int)(x / 64) - 1] == '0')
	{
		x = x - 64;
		y = y + (64 / a);
		ft_check_maplimites(vars, &x, &y, 'w');
	}
	xdm[i].y = (int)(y / 64);
	xdm[i].x = (int)(x / 64);
	tmp = pow(((double)vars->map.cam.posx * 64) + 32 - x, 2) +
		pow(((double)vars->map.cam.posy * 64) + 32 - y, 2);
	len = sqrt(tmp);
	return (len);
}

double	ft_se_hor_inte(t_all *vars, float angle, t_pos *xdm, int i)
{
	double	x;
	double	y;
	double	tmp;
	double	len;
	double	a;

	a = tan(angle);
	if (a < 0)
		a = a * -1;
	x = (double)((vars->map.cam.posx + 1) * 64);
	y = (double)((vars->map.cam.posy * 64) + 32 + (32 / a));
	ft_check_maplimites(vars, &x, &y, 'e');
	while (vars->map.box[(int)(y / 64)][(int)(x / 64)] == '0')
	{
		x = x + 64;
		y = y + (64 / a);
		ft_check_maplimites(vars, &x, &y, 'e');
	}
	xdm[i].y = (int)(y / 64);
	xdm[i].x = (int)(x / 64);
	tmp = pow(((double)vars->map.cam.posx * 64) + 32 - x, 2) +
		pow(((double)vars->map.cam.posy * 64) + 32 - y, 2);
	len = sqrt(tmp);
	return (len);
}

double	ft_hor_intersect(t_all *vars, float angle, t_pos *xdm, int i)
{
	double	res;
	float	fov;
	float	a;

	fov = ft_dir_to_fov(vars->map.cam.dir);
	if (fov > angle)
		a = fov - angle;
	else
		a = angle - fov;
	res = 0;
	if (angle > 0 && angle < (M_PI / 2))
	{
		vars->wallface[i] = 2;
		res = ft_ne_hor_inte(vars, a, xdm, i);
	}
	else if (angle > (M_PI / 2) && angle < M_PI)
	{
		vars->wallface[i] = 1;
		res = ft_nw_hor_inte(vars, a, xdm , i);
	}
	else if (angle > M_PI && angle < (3 * M_PI / 2))
	{
		vars->wallface[i] = 1;
		res = ft_sw_hor_inte(vars, a, xdm , i);
	}
	else
	{
		vars->wallface[i] = 2;
		res = ft_se_hor_inte(vars, a, xdm , i);
	}
	return (res);
}
