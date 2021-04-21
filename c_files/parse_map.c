/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 09:26:42 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/06 07:41:27 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_ismap_member(char c)
{
	if ((c >= '0' && c <= '2') || c == 'N'
			|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int		ft_len_mpline(char *line)
{
	int		i;

	i = 0;
	while (ft_ismap_member(line[i]) || line[i] == ' ')
		i++;
	return (i);
}

char	*ft_linemap_realloc(char **map, int i)
{
	int		j;
	int		len;
	int		maxlen;
	char	*tmp;

	maxlen = ft_lenmax_mpline(map);
	len = ft_len_mpline(map[i]);
	if (!(tmp = malloc(sizeof(char) * (maxlen + 1))))
		return (NULL);
	tmp[maxlen] = '\0';
	j = 0;
	while (j < len)
	{
		tmp[j] = map[i][j];
		j++;
	}
	while (j < maxlen)
	{
		tmp[j] = ' ';
		j++;
	}
	return (tmp);
}

char	*ft_linemap_fill(char *line, int maxlen)
{
	int		i;
	int		len;
	char	*tmp;

	len = ft_len_mpline(line);
	if (!(tmp = malloc(sizeof(char) * (len + 1))))
		return (0);
	tmp[len] = '\0';
	i = 0;
	while (i < len)
	{
		tmp[i] = line[i];
		i++;
	}
	while (i < maxlen)
	{
		tmp[i] = ' ';
		i++;
	}
	return (tmp);
}

char	**ft_parse_map(char *line, char **map)
{
	int		i;
	int		fstdm;
	char	**tmp;

	i = 0;
	while (map[i])
		i++;
	fstdm = i + 1;
	if (!(tmp = malloc(sizeof(char*) * (fstdm + 1))))
		return (NULL);
	tmp[fstdm] = NULL;
	i = 0;
	while (i < (fstdm - 1))
	{
		tmp[i] = ft_linemap_realloc(map, i);
		free(map[i]);
		i++;
	}
	tmp[fstdm - 1] = ft_linemap_fill(line, ft_lenmax_mpline(map));
	free(map);
	return (tmp);
}
