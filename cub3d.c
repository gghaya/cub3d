/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:28:55 by abazerou          #+#    #+#             */
/*   Updated: 2024/01/10 00:30:44 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int W = 13;
int S = 1;
int A = 0;
int D = 2;

int	read_map(t_var *v)
{
	v->map = malloc(sizeof(char *) * (v->map_len + 1));
	if (!v->map)
		return (free(v->map), 1);
	while (v->j < v->map_len)
	{
		v->map[v->j] = get_next_line(v->fd);
		v->j++;
	}
	v->map[v->j] = NULL;
	v->big_line = get_biggest_line(v->map);
	v->new_map = malloc(sizeof(char *) * (v->map_len + 1));
	if (!v->new_map)
		return (free(v->new_map), 1);
	while (v->map[v->i])
	{
		v->new_map[v->i] = v->map[v->i];
		v->i++;
	}
	free(v->map);
	v->new_map[v->i] = NULL;
	return (0);
}
void f(){
    system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_var	v;
	t_info	info;
	t_paths	*paths;
	t_struct *s;
	
	// atexit(f);
	if (ac != 2)
		ft_puterror("Error in arguments!\n", 2);
	v.map_len = 0;
	v.big_line = 0;
	v.i = 0;
	v.j = 0;
	s = malloc(sizeof(t_struct));
	paths = my_malloc(sizeof(t_paths), &s);
	if(!paths || !s)
		ft_puterror("Error : Failed to allocate structs", 2);
	check_ex(av[1]);
	v.fd = open(av[1], O_RDWR);
	if (v.fd == -1)
		ft_puterror("Error in FILE\n!", 2);
	get_map_len(&v, av[1]);
	if (read_map(&v))
		return (1);
	v.i = 0;
	parsing(&v, &paths);
	v.i = 0;
	real_map(&v, &s); // *************************** leaks here;
	info_init(&s);
	init_player(&s);
	put_pixels(&s, &paths);
	mlx_loop(s->mlx);
	free_all(s, &v);
	free(s);
}
