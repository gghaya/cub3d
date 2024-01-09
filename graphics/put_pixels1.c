/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:15:54 by gghaya            #+#    #+#             */
/*   Updated: 2024/01/08 00:12:12 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    draw_sky(t_struct **s, int x, int top_pixel)
{
    int	y;

	y = 0;
	while (y < top_pixel)
	{
		my_mlx_pixel_put(&(*s)->img, x, y, 0x87CEEB);
		y++;
	}
}

void    draw_floor(t_struct **s, int y, int x)
{
	while (y < ((*s)->win_higth))
	{
		my_mlx_pixel_put(&(*s)->img, x, y, 0xA9A9A9);
		y++;
	}
}

void	rendr_util(t_struct **s, t_walls *wall, int i, t_ray *ray)
{
    (void)i;
    wall->correct_dis = ray->distance * cos (ray->ray_angle - (*s)->rot_angle);
    wall->distanceProj = ((*s)->win_width / 2) / tan((*s)->fov_angle / 2);
    wall->pwheight = ((*s)->tail_size / wall->correct_dis) * wall->distanceProj;
    wall->w_stripeheight = (int)wall->pwheight;
    wall->top_pix = ((*s)->win_higth / 2) - (wall->w_stripeheight /  2);
	wall->wbottompx = ((*s)->win_higth / 2) + (wall->w_stripeheight / 2);
    // printf(" ----------------------- %d\n", wall);
    // printf(" ---**************%d\n", ray->ray_angle);
}

void    render_walls(t_struct **s, int x, int texture, t_ray *ray)
{
    t_walls wall;
    int		color;
	int		y;
    int     top_tmp;

    (void)texture;
    top_tmp = 0;
    rendr_util(s, &wall, x, ray);
    if (wall.top_pix < 0 || wall.top_pix > (*s)->win_higth)
	{
		top_tmp = wall.top_pix;
        // printf("---------------------> tmp before : %d\n", top_tmp);
		wall.top_pix = 0;
	}
    // printf("---------------------> TOP PIXEL : %d\n", wall.top_pix);
    // printf("---------------------> tmp NOW : %d\n", abs(top_tmp));
    draw_sky(s, x, wall.top_pix);
    y = wall.top_pix;
    while(y < wall.wbottompx)
    {
        wall.dif = y - wall.top_pix + abs(top_tmp);
        // color = get_color(s, texture, wall.w_stripeheight, wall.dif);
        my_mlx_pixel_put(&(*s)->img, x, y, 0x008000);
		if (y > (*s)->win_higth)
			break ;
		y++;
    }
    draw_floor(s, y, x);
    // printf("---------------> x : %d\n", x);
}