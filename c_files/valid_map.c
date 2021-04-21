/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:50:30 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/06 09:24:24 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_lenmax_mpline(char **map)
{
	int		i;
	int		len;
	int		max;

	max = 0;
	i = 0;
	while(map[i])
	{
		len = ft_len_mpline(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int		ft_is_space_diagwalled_tool(char **map, int i, int j, int len)
{
	int		startx;
	int		starty;

	startx = i;
	starty = j;
	while (i > 0 && j > 0 && map[i][j] != '1' && map[i][j] != ' ')
	{
		i--;
		j--;
	}
	if (map[i][j] != '1')
		return (0);
	i = startx;
	j = starty;
	while (map[i] && j > 0 && map[i][j] != '1' && map[i][j] != ' ')
	{
		i++;
		j--;
	}
	if (map[i][j] != '1')
		return (0);
	return (1);
}

int		ft_is_space_diagwalled(char **map, int i, int j, int len)
{
	int		startx;
	int		starty;

	startx = i;
	starty = j;
	while (map[i] && j < len && map[i][j] != '1' && map[i][j] != ' ')
	{
		i++;
		j++;
	}
	if (map[i][j] != '1')
		return (0);
	i = startx;
	j = starty;
	while (i > 0 && j < len && map[i][j] != '1' && map[i][j] != ' ')
	{
		i--;
		j++;
	}
	if (map[i][j] != '1')
		return (0);
	return (ft_is_space_diagwalled_tool(map, i, j, len));
}

int		ft_is_space_walled(char **map, int i, int j, int len)
{
	int		startx;
	int		starty;

	startx = i;
	starty = j;
	while (i > 0 && map[i][j] != '1' && map[i][j] != ' ')
		i--;
	if (map[i][j] != '1')
		return (0);
	i = startx;
	while (i < len && map[i][j] != '1' && map[i][j] != ' ')
		i++;
	if (map[i][j] != '1')
		return (0);
	while (j > 0 && map[startx][j] != '1' && map[startx][j] != ' ')
		j--;
	if (map[startx][j] != '1')
		return (0);
	while (map[startx] && map[startx][starty] != '1' && map[startx][starty] != ' ')
		starty++;
	if (map[startx][starty] != '1')
		return (0);
	return (1);
}

int		ft_ismap_walled(char **map)
{
	int		i;
	int		j;
	int		len;

	len = ft_lenmax_mpline(map);
	i = 0;
	while (map[i])
	{
		j = ft_len_mpline(map[i]);
		while (j > 0)
		{
			j--;
			if (map[i][j] != '1' && map[i][j] != ' ')
			{
				if (!(ft_is_space_walled(map, i, j, len)))
					return (0);
				if (!(ft_is_space_diagwalled(map, i, j, len)))
					return (0);
			}
		}
		i++;
	}
	return (1);
}
