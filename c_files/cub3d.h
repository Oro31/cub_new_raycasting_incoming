/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 07:56:50 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/06 10:36:52 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <math.h>
# include "../gnl/get_next_line.h"
# include "../minilibx-linux/mlx.h"

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int		bpp;
	int		ll;
	int		e;
}			t_data;

typedef	struct	s_spr
{
	char		**path;
	t_data		*data;
	int		nbspr;
}			t_spr;

typedef	struct	s_rsl
{
	int		w;
	int		h;
}			t_rsl;

typedef	struct	s_rgb
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	int		color;
}			t_rgb;

typedef	struct	s_cam
{
	t_pos		pos;
	char		dir;
}			t_cam;

typedef	struct	s_map
{
	char		**box;
}			t_map;

typedef	struct	s_pos
{
	int		x;
	int		y;
}			t_pos;

typedef	struct	s_ray
{
	double		y;
	double		x;
	int		sy;
	int		sx;
	float		t;
	float		a;
	float		f;
}			t_ray;

typedef	struct	s_all
{
	void		*mlx;
	void		*win;
	int		*wallface;
	t_data		img;
	t_spr		spr;
	t_map		map;
	t_rsl		rsl;
	t_rgb		ground;
	t_rgb		sky;
}			t_all;

int		ft_init(t_all *vars);

void		ft_parse_line(int checkline, t_all *vars, char *line);

char		*ft_parse_path(char *line, int iswall);
int		ft_parse_tex(char *line, char **tpath);

void		ft_parse_rsl(char *line, t_rsl *rsl);
void		ft_define_rslwin(t_all *vars);

void		ft_rgb_fill(t_rgb *rgb, char *line);

int		ft_rgbtocolor(t_rgb *rgb);
t_rgb		*ft_colortorgb(int color);

void		ft_mymlx_pixelput(t_all *vars, t_data *data);
int		ft_myxpm_pixelput(t_all *vars, int e, t_pos *xdm, t_pos *pos);
int		ft_get_pxy(int xy, int wh);
int		ft_get_xpm_pixel(t_data *data, int x, int y);

int		ft_istex_line(char *line);
int		ft_isrgb_line(char *line);
int		ft_ismap_line(char *line);
int		ft_check_line(char *line);

int		ft_ismap_member(char c);
int		ft_len_mpline(char *line);
char		*ft_linemap_realloc(char **map, int i);
char		*ft_linemap_fill(char *line, int maxlen);
char		**ft_parse_map(char *line, char **map);

int		ft_lenmax_mpline(char **map);
int		ft_is_space_diagwalled_tool(char **map, int i, int j, int len);
int		ft_is_space_diagwalled(char **map, int i, int j, int len);
int		ft_is_space_walled(char**map, int i, int j, int len);
int		ft_ismap_walled(char **map);

int		ft_isdigit(int c);

void		ft_fill_sprites(t_all *vars);

void		ft_put_pixel_on_img(t_data *img, int color, int x, int y);
int		ft_get_visual(t_all *vars);
int		ft_draw(t_all *vars);

void		ft_free_sprites(t_all *vars);
void		ft_free_map(t_map *map);
void		ft_exit(t_all *vars);

int		ft_isdir(char c);
char		ft_define_cam(t_map *map);
float		ft_dir_to_fov(char dir);

double		ft_ne_hor_inte(t_all *vars, float angle, t_pos *xdm, int i);
double		ft_nw_hor_inte(t_all *vars, float angle, t_pos *xdm, int i);
double		ft_sw_hor_inte(t_all *vars, float angle, t_pos *xdm, int i);
double		ft_se_hor_inte(t_all *vars, float angle, t_pos *xdm, int i);
double		ft_hor_intersect(t_all *vars, float angle, t_pos *xdm, int i);

double		ft_ne_vert_inte(t_all *vars, float angle, t_pos *xdm, int i);
double		ft_nw_vert_inte(t_all *vars, float angle, t_pos *xdm, int i);
double		ft_sw_vert_inte(t_all *vars, float angle, t_pos *xdm, int i);
double		ft_se_vert_inte(t_all *vars, float angle, t_pos *xdm, int i);
double		ft_vert_intersect(t_all *vars, float angle, t_pos *xdm, int i);

void		ft_check_maplimites(t_all *vars, t_ray *ray);
float		ft_onlyvert_inte(t_all *vars, float angle, t_pos *xdm, int i);
float		ft_onlyhor_inte(t_all *vars, float angle, t_pos *xdm, int i);
double		ft_len_clst_wall(t_all *vars, float angle, t_pos *xdm, int i);
void		ft_find_walls(t_all *vars, double *wall, t_pos *xdm);

int		ft_xdm(t_all *vars, t_pos *xdm, int i);
void		ft_unif_walls(double *wall, int i);

double		ft_new_ver_inte(t_all *vars, t_ray *ray);
double		ft_new_hor_inte(t_all *vars, t_ray *ray);
int		ft_check_wall(t_all *vars, t_ray *ray, char c);
void		ft_define_ray(t_all *vars, t_ray *ray, char c);
void		ft_new_check_maplimites(t_all *vars, int *x, int *y);

#endif
