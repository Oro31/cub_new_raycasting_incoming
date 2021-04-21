/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_hor_inte.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 07:52:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/08 10:46:44 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_new_check_maplimites(t_all *vars, int *x, int *y)
{
	int	i;

	i = 0;
	while (vars->map.box[i])
		i++;
	if (*y >= i)
		*y = i - 1;
	else if (*y < 0)
		*y = 0;
	if (*x >= ft_lenmax_mpline(vars->map.box))
		*x = ft_lenmax_mpline(vars->map.box) - 1;
	else if (*x < 0)
		*x = 0;
}

void	ft_define_ray(t_all *vars, t_ray *ray, char c)
{
	if (ray.a < M_PI && ray.a > 0)
		ray.sy = -1;
	else
		ray.sy = 1;
	if (ray.a > M_PI / 2 && ray.a < 3 * M_PI / 2)
		ray.sx = -1;
	else
		ray.sx = 1;
	if (ray.f == M_PI / 2 || ray.f == 3 * M_PI / 2)
		ray.t = tan(ray.a);
	else
		ray.t = 1 / tan(ray.a);
	if (c == 'v')
		ray.t = 1 / ray.t;
	if (ray.t < 0)
		ray.t *= -1;
}

int	ft_check_wall(t_all *vars, t_ray *ray, char c)
{
	int	x;
	int	y;

	y = (int)(ray.y / 64);
	x = (int)(ray.x / 64);
	if (c == 'h')
	{
		if (ray.a < M_PI && ray.a > 0)
			y -= 1;
	}
	else
	{
		if (ray.a < 3 * M_PI / 2 && ray.a > M_PI / 2)
			x -= 1;
	}
	ft_new_check_maplimites(vars, &x, &y);
	if (vars->map.box[y][x] == '1' || vars->map.box[y][x] == '2')
		return (0);
	return (1);
}

double	ft_new_hor_inte(t_all *vars, t_ray *ray)
{
	double	tmp;

	ft_define_ray(vars, ray, 'h');
	ray.y = (double)((vars->cam.pos.y + (1 + ray.sy) / 2) * 64);
	ray.x = (double)(vars->cam.pos.x * 64) + 32 + ray.sx * 32 * ray.t;
	while (ft_check_wall(vars, ray, 'h'))
	{
		ray.x += ray.sx * 64 * ray.t;
		ray.y += ray.sy * 64;
	}
	tmp = pow(((double)vars->cam.pos.y * 64) + 32 - ray.y, 2) +
		pow(((double)vars->cam.pos.x * 64) + 32 - ray.x, 2);
	return (sqrt(tmp));
}

double	ft_new_ver_inte(t_all *vars, t_ray *ray)
{
	double	tmp;

	ft_define_ray(vars, ray, 'v');
	ray.x = (double)((vars.cam.pos.x + (1 + ray.sx) / 2) * 64);
	ray.y = (double)(vars->cam.pos.y * 64) + 32 + ray.sy * 32* ray.t;
	while (ft_check_wall(vars, ray, 'v'))
	{
		ray.y += ray.sy * 64 * ray.t;
		ray.x += ray.sx * 64;
	}
	tmp = pow(((double)vars->cam.pos.y * 64) + 32 - ray.y, 2) +
		pow(((double)vars->cam.pos.x * 64) + 32 - ray.x, 2);
	return (sqrt(tmp));
}
