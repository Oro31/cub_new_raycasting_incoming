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

int	main()
{
	int	fd;
	char	*line;
	t_all	vars;
	int	i;

	printf("start \n");
	ft_init(&vars);
	if (!(fd = open("map.cub", O_RDONLY)))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		printf("gnl running /\n");
		ft_parse_line(ft_check_line(line), &vars, line);
	}
	printf("is map walled ? %d \n", ft_ismap_walled(vars.map.box));
	i = 0;
	while (vars.spr.path[i])
	{
		printf("texpath[%d] = %s \n", i, vars.spr.path[i]);
		i++;
	}
	i = 0;
	while(vars.map.box[i])
	{
		printf("map[%d] = %s \n", i , vars.map.box[i]);
		i++;
	}
	printf("before fill sprites \n");
	ft_fill_sprites(&vars);
	vars.ground.color = ft_rgbtocolor(&vars.ground);
	vars.sky.color = ft_rgbtocolor(&vars.sky);
	ft_define_rslwin(&vars);
	vars.map.cam.dir = ft_define_cam(&vars.map);
	if (!(vars.wallface = malloc(sizeof(int) * vars.rsl.w)))
		return (0);
	vars.wallface[vars.rsl.w - 1] = -1;
	printf("posx = %d, posy = %d, dir:%c \n", vars.map.cam.posx, vars.map.cam.posy, vars.map.cam.dir);
	if (ft_draw(&vars) == 0)
		return (0);
	printf("before exit \n");
	/*ft_exit(&vars);*/
	printf("after exit \n");
	mlx_loop(vars.mlx);
	close(fd);
	return (0);
}
