/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 08:09:32 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/05 11:15:36 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_rsl(char *line, t_rsl *rsl)
{
	int		i;
	int		r;

	r = 0;
	i = 2;
	while (line[i] == ' ')
		i++;
	while(ft_isdigit(line[i]))
	{
		r = r * 10 + (line[i] - 48);
		i++;
	}
	rsl->w = r;
	r = 0;
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
	{
		r = r * 10 + (line[i] - 48);
		i++;
	}
	rsl->h = r;
	printf("parse rsl OK \n");
}

void	ft_define_rslwin(t_all *vars)
{
	vars->win = mlx_new_window(vars->mlx, vars->rsl.w, vars->rsl.h, "cub");
}
