/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:32:40 by abazerou          #+#    #+#             */
/*   Updated: 2024/01/13 21:13:51 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_dup(char **map, t_var *v)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	while (i < v->map_pos)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] && map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
				flag++;
			j++;
		}
		i++;
	}
	if (flag != 4)
		ft_puterror("Error: duplicated path\n", 2);
}

void	skip_space(t_var *v)
{
	while (v->new_map[v->x][v->skip] && v->new_map[v->x][v->skip] == ' ')
		v->skip++;
	v->save = v->skip;
	while (v->new_map[v->x][v->skip] && v->new_map[v->x][v->skip] != ' ')
		v->skip++;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_puterror(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	exit (1);
}
