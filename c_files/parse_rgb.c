/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:18:59 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/05 12:43:26 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rgb_fill(t_rgb *rgb, char *line)
{
	int		i;
	int		ret;
	uint8_t	tmp;

	rgb->r = 0;
	rgb->g = 0;
	rgb->b = 0;
	ret = 0;
	i = 0;
	while (ret == 0 && line[i])
	{
		while (!(ft_isdigit(line[i])))
			i++;
		tmp = 0;
		while (ft_isdigit(line[i]))
		{
			tmp = tmp * 10 + (line[i] - 48);
			i++;
		}
		printf("tmp rgb %u \n", tmp);
		if (rgb->r != 0 && rgb->g != 0 && rgb->b == 0)
			rgb->b = tmp;
		else if (rgb->r != 0 && rgb->g == 0 && rgb->b == 0)
			rgb->g = tmp;
		else if (rgb->r == 0 && rgb->g == 0 && rgb->b == 0)
			rgb->r = tmp;
		else
			ret = 0;
	}
	printf("parse rgb OK \n");
}
