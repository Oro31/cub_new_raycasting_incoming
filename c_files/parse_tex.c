/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 07:34:12 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/02 09:16:16 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_parse_path(char *line, int iswall)
{
	char	*tmp;
	int		j;
	int		spc;
	int		start;

	start = 2 + iswall;
	j = start;
	while (line[j] == ' ')
		j++;
	spc = j - start;
	while (line[j] != '\0' && line[j] != '\n')
		j++;
	if (!(tmp = malloc(sizeof(char) * (j - (spc + start) + 1))))
		return (NULL);
	tmp[j - (spc + start)] = '\0';
	j = start + spc;
	while (line[j] != '\0' && line[j] != '\n')
	{
		tmp[j - (spc + start)] = line[j];
		j++;
	}
	return (tmp);
}

int		ft_parse_tex(char *line, char **tpath)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		tpath[0] = ft_parse_path(line, 1);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		tpath[1] = ft_parse_path(line, 1);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		tpath[2] = ft_parse_path(line, 1);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		tpath[3] = ft_parse_path(line, 1);
	else if (line[0] == 'S' && line[1] == ' ')
		tpath[4] = ft_parse_path(line, 0);
	return (1);
}
