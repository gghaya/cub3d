/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:53:05 by abazerou          #+#    #+#             */
/*   Updated: 2024/01/09 21:17:12 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "stdio.h"
# include "stdlib.h"
# include <fcntl.h>
# include "../get_next_line/get_next_line.h"
# include "../Libft/libft.h"
#include<mlx.h>
#include<math.h>
#include <limits.h>
# include <stdbool.h>

#define HEIGHT 1000
#define WIDTH 1000
#define MINI 1


extern int W;
extern int S;
extern int A;
extern int D;
// extern int NUM;



//****** PLAYER DIRECTION PATHS ******
typedef struct s_rgb
{
	int	floor[3];
	int	ceiling[3];

}	t_rgb;
//****** PLAYER informations ******

typedef struct	s_player {
	int		x;
	int		y;
	int		radius;
	int		turn_dirct;
	int		walk_dirct;
	double	rot_angle;
	double move_speed;
	double	rot_speed;


}	t_player	;
// ***********************

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int width;
	int height;
}				t_data;
//******** PARSING STRUCT *****************
typedef struct s_var
{
	char	**map;
	char	**new_map;
	char	*new_line;
	char	**numbers;
	char	*s;
	char	*str[4];
	int		fd;
	int		fd1;
	int		i;
	int		j;
	int		n;
	int		x;
	int		y;
	int		v;
	int		index;
	int		flag;
	int		map_len;
	int		map_pos;
	int		player_pos;
	int		flag_f;
	int		flag_c;
	int		start;
	size_t	big_line;
	size_t	len_s;
	t_rgb	*rgb;
	char	**real_map;

}	t_var;

typedef struct s_info
{
	int tail_size;
	int map_rows;
	int map_cols;
	int win_width;
	int win_higth;
	int player_x;
	int player_y;
	int fov_angle;
	int wall_width ;
	int num_rays;
	char player_rot;
	t_player	player;
}	 t_info;

//****** PLAYER DIRECTION PATHS ********
typedef struct s_paths
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_paths;

//******** MLX STRUCT ********
typedef struct s_mlx
{
	void		*mlx;
	void	*win;
	int			x;
	int			y;
	t_var		*v;

}	t_mlx;
typedef struct s_inter
{
	double x;
	double y;
	double dist;
	bool 	hit_v;
	bool 	hit_h;
} t_inter;
typedef struct s_ray
{
	double ray_angle;
	double hit_x;
	double hit_y;
	double distance;
	int hit_vertical;
	int facing_up;
	int facing_down;
	int facing_right;
	int facing_left;
	int hit_content;
} t_ray;
typedef struct s_struct
{
	int tail_size;
	int map_rows;
	int map_cols;
	int win_width;
	int win_higth;
	double player_x;
	double player_y;
	double real_x;
	double real_y;
	double fov_angle;
	int wall_width ;
	int num_rays;
	char	**map;
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		radius;
	int		turn_dirct;
	int		walk_dirct;
	double	rot_angle;
	double 	move_speed;
	double	rot_speed;
	double 	delta_x;
	double delta_y;
	t_data	img;
 	t_ray  *rays;

} t_struct;

typedef struct s_walls
{
	double	pwheight;
	double	distanceProj;
	double	correct_dis;
	int		dif;
	int		top_pix;
	int		wbottompx;
	int		w_stripeheight;
}	t_walls;

//*********** PARSING *************
void	parsing(t_var *v);
void	ft_puterror(char *s, int fd);
void	check_ex(char *s);
int		get_biggest_line(char **str);
void	parse_path(char **map, t_var *v);
int		check_right(char *map, int i);
int		check_left(char *map, int i);
int		check_up(char **map, int i, int j);
int		check_down(char **map, int i, int j, t_var *v);
char	**join_space(char **map, t_var *v);
int		count_directions(char **map, t_var *v);
void	ft_freetab(char **map);
void	get_map_len(t_var *v, char *str);
int		read_map(t_var *v);
char	**fill_empty(char **map, t_var *v);
void	check_valid_chars(char **map, t_var *v);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(char *s1, char *s2);
void	search_map(char **map, t_var *v);
int		check_digit(char **str, int i, int j);
void	count_id(t_var *v, int i, int j);
void	start_parser(t_var *v, int i, int j);
int		check_id(t_var *v);
void	get_player_pos(t_var *v);
int		is_comma(char **str, int i, int j);
int		check_digit(char **str, int i, int j);
int		check_after_d(char **str, int i, int j);
void	is_opened(char *s[]);
void	check_rgb_range(t_var *v, int i, int j);
void	is_range_valid(t_var *v, char **numbers);
void	is_rgb_valid(t_var *v);
void	check_id_help(t_var *v, int i, int n);
void	ft_free(char *s[]);
int	ft_strchrr(const char *string, int searchedChar);
void init_player(t_struct **s);

//******** GRAPHICS ***********
void 	real_map(t_var *var, t_struct **s);
void	info_init(t_struct **s);
void	put_pixels(t_struct **s);
void    put_(t_struct **s);
void	rendr_util(t_struct **s, t_walls *wall, int i, t_ray *ray);
void    render_walls(t_struct **s, int x, int texture, t_ray *ray);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif