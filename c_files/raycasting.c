/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:06:15 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/05 11:15:31 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_maplimites(t_all *vars, t_ray *ray)
{
        int     j;
        int     xmax;
	int	absc;
	int	ord;

	absc = (int)(ray.x / 64);
	ord = (int)(ray.y / 64);
	if (ray.a < 3 * M_PI / 2 && ray.a > M_PI / 2)
		absc -= 1;
	else if (ray.a < M_PI && ray.a > 0)
		ord -= 1;
        j = 0;
        while (vars->map.box[j])
                j++;
        if (ord >= j)
                ray.y = (double)((j - 1) * 64);
        else if (ord < 0)
                ray.y = 0;
        xmax = ft_lenmax_mpline(vars->map.box);
        if (absc < 0)
                ray.x = 0;
        else if (absc > xmax)
                ray.x = (xmax - 1) * 64;
}

float	ft_onlyvert_inte(t_all *vars, float angle, t_pos *xdm, int i)
{
	int	y;
	int	x;
	int	signe;
	float	tmp;
	float	len;

	printf("onlyvert : angle = %f \n", angle);
	signe = 1;
	if (angle < ((M_PI / 2) + 0.001) && angle > ((M_PI / 2) - 0.001))
		signe = -1;
	y = vars->map.cam.posy + signe;
	x = vars->map.cam.posx;
	while (vars->map.box[y][x] == '0')
		y += signe;
	xdm[i].x = x;
	xdm[i].y = y + 1;
	printf("x = %d, y = %d", x, y);
	tmp = pow((vars->map.cam.posx * 64) + 32 - (x * 64), 2) +
		pow((vars->map.cam.posy * 64) + 32 - ((y + 1) * 64), 2);
	len = sqrt(tmp);
	return (len);
}

float	ft_onlyhor_inte(t_all *vars, float angle, t_pos *xdm, int i)
{
	int	x;
	int	y;
	int	signe;
	float	tmp;
	float	len;

	printf("onlyvert : angle = %f \n", angle);
	signe = 1;
	if (angle == M_PI)
		signe = -1;
	x = vars->map.cam.posx + signe;
	y = vars->map.cam.posy;
	while (vars->map.box[y][x] == '0')
		x += signe;
	xdm[i].x = x;
	xdm[i].y = y;
	tmp = pow((vars->map.cam.posx * 64) + 32 - (x * 64), 2) +
		pow((vars->map.cam.posy * 64) + 32 - (y * 64), 2);
	len = sqrt(tmp);
	return (len);
}

double	ft_len_clst_wall(t_all *vars, float angle, t_pos *xdm, int i)
{
	double	x;
	double	y;
	float	fov;
	float	a;
	float	cosbeta;

	while (angle < 0)
		angle += 2 * M_PI;
	while (angle > (2 * M_PI))
		angle -= 2 * M_PI;
	if ((angle < ((M_PI / 2) + 0.001) && angle > ((M_PI / 2) - 0.001)) ||
			(angle < ((3 * M_PI / 2) + 0.001) &&
			angle > ((3 * M_PI / 2) - 0.001)))
		return (ft_onlyvert_inte(vars, angle, xdm, i));
	else if (angle == 0 || angle == M_PI)
		return (ft_onlyhor_inte(vars, angle, xdm, i));
	x = ft_hor_intersect(vars, angle, xdm, i);
	y = ft_vert_intersect(vars, angle, xdm , i);
	fov = ft_dir_to_fov(vars->map.cam.dir);
	if (fov > angle)
		a = fov - angle;
	else
		a = angle - fov;
	cosbeta = cos(a);
	if (cosbeta < 0)
		cosbeta *= -1;
	if (x >= y)
		return (ft_vert_intersect(vars, angle, xdm, i) * cosbeta);
	else
		return (ft_hor_intersect(vars, angle, xdm, i) * cosbeta);
}

void	ft_find_walls(t_all *vars, double *wall, t_pos *xdm)
{
	int	i;
	float	a;
	float	fov;

	a = (M_PI / 3) / vars->rsl.w;
	fov = ft_dir_to_fov(vars->map.cam.dir);
	i = 0;
	while (i < vars->rsl.w)
	{
		wall[i] = ft_len_clst_wall(vars,
				(fov + (M_PI / 6)) - (i * a), xdm, i);
		/*printf("angle = %f \n", (fov + (M_PI / 6) - (i * a)));
		printf("wall[%d] = %f \n", i, wall[i]);*/
		i++;
	}
	ft_unif_walls(wall, i);
}
