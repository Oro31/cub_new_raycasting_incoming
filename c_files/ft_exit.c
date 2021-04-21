/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 07:46:41 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/06 08:42:09 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_sprites(t_all *vars)
{
	int	i;

	i = 0;
	while (vars->spr.path[i])
	{
		free(vars->spr.path[i]);
		i++;
	}
	free(vars->spr.path);
	i = 0;
	while (i < vars->spr.nbspr)
	{
		mlx_destroy_image(vars, vars->spr.data[i].img);
		i++;
	}
	free(vars->spr.data);
}

void	ft_free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->box[i])
	{
		free(map->box[i]);
		i++;
	}
	free(map);
}

void	ft_exit(t_all *vars)
{
	ft_free_sprites(vars);
	ft_free_map(&vars->map);
}
