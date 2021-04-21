/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 07:46:41 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/06 08:42:09 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixel_on_img(t_data *img, int color, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int	ft_get_visual(t_all *vars)
{
	double	*wall;
	t_pos	pos;
	t_pos	*xdm;
	int	e;
	int	color;

	if (!(wall = malloc(sizeof(double) * vars->rsl.w)))
		return (0);
	if (!(xdm = malloc(sizeof(t_pos) * vars->rsl.w)))
		return (0);
	ft_find_walls(vars, wall, xdm);
	printf("find walls ok \n");
	pos.x = 0;
	while (pos.x < vars->rsl.w)
	{
		/*printf("wall[%d] = %f; ", pos.x, wall[pos.x]);*/
		pos.y = -1;
		e = (vars->rsl.h - ((64 * 350) / wall[pos.x])) / 2;
		/*printf("e = %d \n", e);*/
		while (++pos.y < (e - 1))
			ft_put_pixel_on_img(&vars->img, vars->sky.color,
				       	pos.x, pos.y);
		while (++pos.y < (vars->rsl.h - e))
		{
			color = ft_myxpm_pixelput(vars, e, xdm, &pos);
			ft_put_pixel_on_img(&vars->img, color, pos.x, pos.y);
		}
		while (++pos.y < vars->rsl.h)
			ft_put_pixel_on_img(&vars->img, vars->ground.color,
					pos.x, pos.y);
		pos.x++;
	}
	printf("draw ok \n");
	return (1);
}

int	ft_draw(t_all *vars)
{
	vars->img.img = mlx_new_image(vars->mlx, vars->rsl.w, vars->rsl.h);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bpp, 
			&vars->img.ll, &vars->img.e);
	/*ft_mymlx_pixelput(vars, &vars->img);*/
	printf("before get visual");
	if (ft_get_visual(vars) == 0)
		return (0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (1);
}
