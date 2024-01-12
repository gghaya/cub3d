/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:23:48 by abazerou          #+#    #+#             */
/*   Updated: 2024/01/12 19:11:38 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void init_funct(t_struct **s, t_paths **path)
{
	(*s)->mlx = mlx_init();
	(*s)->win = mlx_new_window((*s)->mlx, (*s)->win_width, (*s)->win_higth, "CUB3D");
	read_textures(s, path);
	(*s)->img.img = mlx_new_image((*s)->mlx, (*s)->win_width, (*s)->win_higth);
	(*s)->img.addr = mlx_get_data_addr((*s)->img.img, &((*s)->img.bits_per_pixel), &((*s)->img.line_length),
								&((*s)->img.endian));
}

void draw_line(t_data *img, double beginX, double beginY, double endX, double endY, double color)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		// mlx_pixel_put(mlx, win, pixelX, pixelY, color);
		my_mlx_pixel_put(img, pixelX, pixelY, color);
		// printf("%f , %f \n", pixelX, pixelY );
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	// printf("fin\n");
}
// void    draw_line_dda(t_data *img, double beginX, double beginY, double endX, double endY, double colorw)
// {
//     int        d[2];
//     int        i;
//     int        step;
//     float    x[2];
//     float    inc[2];

//     i = 0;
// 	d[0] = endX - beginX;
//      d[1] = endY - beginY;
//     if (abs(d[0]) > abs(d[1]))
//         step = abs(d[0]);
//     else
//         step = abs(d[1]);
//     inc[0] = (float)d[0] / (float)step;
//     inc[1] = (float)d[1] / (float)step;
//     x[0] = beginX;
//     x[1] = beginY;
//     while (i < step /*&& x[0] <= 128 && x[1] <= 128*/)
//     {
//         my_mlx_pixel_put(img, floor(x[0]), floor(x[1]), 0xeb4034);
//         x[0] += inc[0];
//         x[1] += inc[1];
//         i++;
//     }
// }
void draw_line_dda(t_data *img, double beginX, double beginY, double endX, double endY, double color) {
    double deltaX = endX - beginX;
    double deltaY = endY - beginY;

    int steps;
    if (fabs(deltaX) > fabs(deltaY)) {
        steps = round(fabs(deltaX));
    } else {
        steps = round(fabs(deltaY));
    }

    double xIncrement = (float)deltaX / (float)steps;
    double yIncrement = (float)deltaY / (float)steps;

    double x = beginX;
    double y = beginY;

    for (int i = 0; i <= steps; ++i) {
        my_mlx_pixel_put(img, round(x), round(y), color);
        x += xIncrement;
        y += yIncrement;
    }
}

void    draw_rays(t_struct **s)
{
    // int    i;
    // int    ox;
    // int    oy;
    // i = 0;
    // while (i <= 50)
    // {
    //     ox =(*s)->player_x+16 - (i *cos(angle));
    //     oy = (*s)->player_y+16 - (i * sin(angle));
    //     my_mlx_pixel_put(&((*s)->img), ox, oy, 0xff6700);
    //     i++;
    // }
    my_mlx_pixel_put(&((*s)->img), (((*s)->player_x + 32) + 50 * cos((*s)->rot_angle)) * MINI, (((*s)->player_y + 32 )+ 50 * sin((*s)->rot_angle)) * MINI, 0x000000);
}


t_ray fill_info(t_inter r1, t_ray ray, int vert)
{
	ray.distance = r1.dist;
	ray.hit_x = r1.x;
	ray.hit_y = r1.y;
	ray.hit_vertical = vert;
	return (ray);
}

void	drawingray(t_ray all, t_struct  **s)
{
	int		d[2];
	int		i;
	int		step;
	float	x[2];
	float	inc[2];

	i = 0;
	d[0] = all.hit_x - ((*s)->player_x) ;
	d[1] = all.hit_y - ((*s)->player_y) ;
	if (abs(d[0]) > abs(d[1]))
		step = abs(d[0]);
	else
		step = abs(d[1]);
	inc[0] = (float)d[0] / (float)step;
	inc[1] = (float)d[1] / (float)step;
	x[0] =  ((*s)->player_x);
	x[1] =  ((*s)->player_y);
	while (i < step )
	{
		my_mlx_pixel_put(&(*s)->img, floor(x[0]), floor(x[1]), 0xeb4034);
		x[0] += inc[0];
		x[1] += inc[1];
		i++;
	}
}

void    push_rays(t_struct **s)
{
    int    i;
    int    ox;
    int    oy;
    i = 0;
    while (i <= 30)
    {
        ox =(*s)->player_x+16 - (i *cos((*s)->rot_angle));
        oy = (*s)->player_y+16 - (i * sin((*s)->rot_angle));
        my_mlx_pixel_put(&((*s)->img), ox, oy, 0xff6700);
        i++;
    }
}


void draw_disk(t_struct	**s)
{
    // int x, y;
	// int center_x = (*s)->player_x+15;
	// int center_y = (*s)->player_y+15;
	// int radius = 10;
    // for (x = center_x - radius; x <= center_x + radius; x++)
    // {
    //     for (y = center_y - radius; y <= center_y + radius; y++)
    //     {
    //         double distance = sqrt(pow(x - center_x, 2) + pow(y - center_y, 2));

    //         if (distance <= radius)
    //             my_mlx_pixel_put(&(*s)->img, x, y, 0x27222c); // Dessine un pixel blanc à l'intérieur du disque
    //     }
    // }
	// int i = 0;
	// int j;
	// while (i < 20)
	// {
	// 	j = 0;
	// 	while (j < 20)
	// 	{
			my_mlx_pixel_put(&(*s)->img, ((*s)->player_x + 32) * MINI, ((*s)->player_y +32) * MINI, 0x000000); // Dessine un pixel blanc à l'intérieur du disque
			// j++;
	// 	}
	// 	i++;
	// }
}
void    put_(t_struct **s)
{
	cast_rays(s);
	// int j =0;
	// int i =0;
	// int k =0;
	// int l= 0;
	// 	k = 0;

	// while ((*s)->map[k])
	// {
	// 	l = 0;
	// 	while ((*s)->map[k][l])
	// 	{
	// 		i = 0;
	// 		while (i < 63)
	// 		{
	// 			j = 0;
	// 			while (j < 63)
	// 			{
	// 				if ((*s)->map[k][l] == '1')
	// 					my_mlx_pixel_put(&((*s)->img), ((l*(*s)->tail_size)+j) * MINI, ((k*(*s)->tail_size)+i )* MINI, 0x2c446d);
	// 				else if ((*s)->map[k][l] == '0' || ft_strchrr("NSWE", (*s)->map[k][l]) == 1)
	// 						my_mlx_pixel_put(&((*s)->img), ((l*(*s)->tail_size)+j) * MINI, ((k*(*s)->tail_size)+i) * MINI, 0xece7dd);
	// 				j++;
	// 			}
	// 			i++;
	// 		}
	// 		l++;
	// 	}
	// 	k++;
	// }
	// push_rays(s);
	// draw_disk(s);
	// draw_rays(s);
	// for (int i = 0; i < (*s)->num_rays; i++)
	// {
		
	// }
	mlx_put_image_to_window((*s)->mlx,(*s)->win, (*s)->img.img, 0, 0);
}


void manage_events(t_struct **s)
{
	mlx_hook((*s)->win, 3, 0, key_released, (s));
	mlx_hook((*s)->win, 2, 0, key_pressed, (s));
	mlx_hook((*s)->win, 17, 0, key_exit, (s));
	mlx_loop_hook((*s)->mlx, &update_info, (s));
}

void    put_pixels(t_struct **s, t_paths **path)
{
	init_funct(s, path);
	manage_events(s);
}
