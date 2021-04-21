/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 07:46:41 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/06 08:42:09 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_ne_vert_inte(t_all *vars, float angle, t_pos *xdm, int i)
{
	double	y;
	double	x;
	double	tmp;
	double	len;
	double	a;

	a = tan(angle);
	if (a < 0)
		a = a * -1;
	y = (double)(vars->map.cam.posy * 64);
	x = ((double)vars->map.cam.posx * 64) + 32 + (32 * a);
	ft_check_maplimites(vars, &x, &y, 'n');
	while (vars->map.box[(int)(y / 64) - 1][(int)(x / 64)] == '0')
	{
		y = y - 64;
		x = x + (64 * a);
		ft_check_maplimites(vars, &x, &y, 'n');
	}
	xdm[i].y = (int)(y / 64);
        xdm[i].x = (int)(x / 64);
	tmp = pow(((double)vars->map.cam.posy * 64) + 32 - y, 2) + 
		pow(((double)vars->map.cam.posx * 64) + 32 - x, 2);
	len = sqrt(tmp);
	return (len);
}

double	ft_nw_vert_inte(t_all *vars, float angle, t_pos *xdm, int i)
{
	double	y;
	double	x;
	double	tmp;
	double	len;
	double	a;

	a = tan(angle);
	if (a < 0)
		a = a * -1;
	y = (double)(vars->map.cam.posy * 64);
	x = ((double)vars->map.cam.posx * 64) + 32 - (32 * a);
	ft_check_maplimites(vars, &x, &y, 'n');
	while (vars->map.box[(int)(y / 64) - 1][(int)(x / 64)] == '0')
	{
		y = y - 64;
		x = x - (64 * a);
		ft_check_maplimites(vars, &x, &y, 'n');
	}
	xdm[i].y = (int)(y / 64);
        xdm[i].x = (int)(x / 64);
	tmp = pow(((double)vars->map.cam.posy * 64) + 32 - y, 2) + 
		pow(((double)vars->map.cam.posx * 64) + 32 - x, 2);
	len = sqrt(tmp);
	return (len);
}

double	ft_sw_vert_inte(t_all *vars, float angle, t_pos *xdm, int i)
{
	double	y;
	double	x;
	double	tmp;
	double	len;
	double	a;

	a = tan(angle);
	if (a < 0)
		a = a * -1;
	y = (double)((vars->map.cam.posy + 1) * 64);
	x = ((double)vars->map.cam.posx * 64) + 32 - (32 * a);
	ft_check_maplimites(vars, &x, &y, 's');
	while (vars->map.box[(int)(y / 64)][(int)(x / 64)] == '0')
	{
		y = y + 64;
		x = x - (64 * a);
		ft_check_maplimites(vars, &x, &y, 's');
	}
	xdm[i].y = (int)(y / 64);
        xdm[i].x = (int)(x / 64);
	tmp = pow(((double)vars->map.cam.posy * 64) + 32 - y, 2) + 
		pow(((double)vars->map.cam.posx * 64) + 32 - x, 2);
	len = sqrt(tmp);
	return (len);
}

double	ft_se_vert_inte(t_all *vars, float angle, t_pos *xdm, int i)
{
	double	y;
	double	x;
	double	tmp;
	double	len;
	double	a;

	a = tan(angle);
	if (a < 0)
		a = a * -1;
	y = (double)((vars->map.cam.posy + 1) * 64);
	x = ((double)vars->map.cam.posx * 64) + 32 + (32 * a);
	ft_check_maplimites(vars, &x, &y, 's');
	while (vars->map.box[(int)(y / 64)][(int)(x / 64)] == '0')
	{
		y = y + 64;
		x = x + (64 * a);
		ft_check_maplimites(vars, &x, &y, 's');
	}
	xdm[i].y = (int)(y / 64);
        xdm[i].x = (int)(x / 64);
	tmp = pow(((double)vars->map.cam.posy * 64) + 32 - y, 2) + 
		pow(((double)vars->map.cam.posx * 64) + 32 - x, 2);
	len = sqrt(tmp);
	return (len);
}

double	ft_vert_intersect(t_all *vars, float angle, t_pos *xdm, int i)
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
		vars->wallface[i] = 3;
		res = ft_ne_vert_inte(vars, a, xdm, i);
	}
	else if (angle > (M_PI / 2) && angle < M_PI)
	{
		vars->wallface[i] = 3;
		res = ft_nw_vert_inte(vars, a, xdm , i);
	}
	else if (angle > M_PI && angle < (3 * M_PI / 2))
	{
		vars->wallface[i] = 0;
		res = ft_sw_vert_inte(vars, a, xdm , i);
	}
	else
	{
		vars->wallface[i] = 0;
		res = ft_se_vert_inte(vars, a, xdm , i);
	}
	return (res);
}
