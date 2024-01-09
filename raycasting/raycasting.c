/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:08:04 by gghaya            #+#    #+#             */
/*   Updated: 2024/01/09 21:50:35 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"
#include"../Libft/libft.h"
#include <stdlib.h>
#include <math.h>

int	ft_strchrr(const char *string, int searchedChar)
{
	int		i;
	char	c;

	c = (char)searchedChar;
	i = 0;
	while (string[i])
	{
		if ((char)string[i] == c)
			return (1);
		i++;
	}
	return (0);
}
static int	ft_searchc(char *string, char c)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	if (!s1 || !set)
		return (0);
	j = ft_strlen(s1) - 1;
	while (j >= i && ft_searchc((char *)set, s1[j]))
		j--;
	return (ft_substr(s1, i, j - i +1));
}

char	*pure_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	if (!s1 || !set)
		return (0);
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_searchc((char *)set, s1[i]))
		i++;
	while (j >= i && ft_searchc((char *)set, s1[j]))
		j--;
	return (ft_substr(s1, i, j - i +1));
}
void    real_map(t_var *var, t_struct **s)
{
    char *line = malloc(sizeof(char)*10);
    int i = 0;
    int begin = 0;
    size_t j;
    size_t len;
    char * set = " ";
    
    while ((var->new_map[i][0] != ' ' && var->new_map[i][0] != '1' && var->new_map[i][0] != '0') || ft_strlen(pure_strtrim(var->new_map[i], set)) == 0)
        i++;
    begin = i;
    len = ft_strlen(ft_strtrim(var->new_map[i], set));
    i++;
    while (var->new_map[i])
    {
        if (ft_strlen(ft_strtrim(var->new_map[i], set)) > len)
            len = ft_strlen(ft_strtrim(var->new_map[i], set));
        i++;
    }
    (*s)->map = malloc(sizeof(char *)*((i - begin) + 2));
    if (!(*s)->map)
        return ;
    i = 0;
    while (var->new_map[begin])
    {
        line = ft_strtrim(var->new_map[begin], set);
        (*s)->map[i] =  (char *)malloc(sizeof(char)*(len+1));
        if (!((*s)->map[i]))
            return ;
        j = 0;
        while((j < len))
        {
            if (j < ft_strlen(line) && line[j] && (ft_strchrr("10NEWS", line[j]) == 1 ))
                (*s)->map[i][j] = line[j];
            else 
                (*s)->map[i][j] = '1';
            j++;
        }
        (*s)->map[i][len] = '\0';
        i++;
        begin++;
        int k = ft_strlen(line);
        ft_bzero(line, k);
        free(line);
    }
    (*s)->map[i] = NULL;
}

void   info_init(t_struct **s)
{
	int i = 0;
    int j = 0;
    while((*s)->map[i][j])
        j++;
    while ((*s)->map[i])
        i++;
    (*s)->map_rows = i;
    (*s)->map_cols = j;
    (*s)->tail_size = 64;
    (*s)->win_width =  WIDTH;
    (*s)->img.width = (*s)->win_width;
    (*s)->win_higth = HEIGHT;
    (*s)->img.height = (*s)->win_higth;
    (*s)->fov_angle = 60*(M_PI/2/180);
	(*s)->wall_width = 1;
	(*s)->num_rays = ((*s)->win_width/(*s)->wall_width);
    (*s)->delta_x = 0;
    (*s)->delta_y = 0;
}