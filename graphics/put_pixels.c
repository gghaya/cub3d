/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:23:48 by abazerou          #+#    #+#             */
/*   Updated: 2024/01/10 00:53:38 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void 	ft_direction(t_struct **s)
{
	if ((*s)->x > 0 && (*s)->x < (*s)->map_rows && (*s)->y > 0 && (*s)->y < (*s)->map_cols)
	{
		if ((*s)->map[(*s)->x][(*s)->y] == 'E')
			(*s)->rot_angle = M_PI;
		else if ((*s)->map[(*s)->x][(*s)->y] == 'N')
			(*s)->rot_angle = M_PI_2;
		else if((*s)->map[(*s)->x][(*s)->y] == 'W')
			(*s)->rot_angle = 0;
		else if((*s)->map[(*s)->x][(*s)->y] == 'S')
			(*s)->rot_angle = M_PI * 3 / 2;
		
	}
}


void norm(t_struct **s)
{
    (*s)->rot_angle = fmod((*s)->rot_angle, 2 * M_PI);
    if ((*s)->rot_angle < 0)
       (*s)->rot_angle += 2 * M_PI;
}
double normalize(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    // Ensure the angle is not negative
    if (angle < 0)
       angle += 2 * M_PI;
	return (angle);
}
void init_player(t_struct **s)
{
	int i =0;
	int j;

	while ((*s)->map[i])
	{
		j = 0;
		while ((*s)->map[i][j])
		{
			if (ft_strchrr("WSEN",(*s)->map[i][j]))
			{
				(*s)->x = j;
				(*s)->y = i;
				ft_direction(s);
			}
			j++;
		}	
		i++;
	}
	(*s)->player_x = (*s)->x * (*s)->tail_size;
	(*s)->player_y = (*s)->y * (*s)->tail_size;
	(*s)->real_y = (*s)->y * (*s)->tail_size;
	(*s)->real_x = (*s)->x * (*s)->tail_size;
	(*s)->turn_dirct =0;
	(*s)->walk_dirct=0;
	(*s)->move_speed = 15.0;
	(*s)->rot_speed= 3*(M_PI/180);
}
int key_pressed(int key_code, t_struct **s)
{

	if (key_code == 53)
		exit(0);
	else if (key_code == W)
		(*s)->delta_y = 1;
	else if (key_code == A)
		(*s)->delta_x = -1;
	else if (key_code == S)
		(*s)->delta_y = -1;
	else if (key_code == D)
		(*s)->delta_x = 1;
	else if (key_code == 123)
		(*s)->turn_dirct = -1;
	else if (key_code == 124)
		(*s)->turn_dirct = 1;
	printf("key_pressed\n");
	return(0);
}

int key_released(int key_code,t_struct **s)
{
	if (key_code == A)
		(*s)->delta_x =0;
	if (key_code == W)
		(*s)->delta_y =0;
	else if (key_code == S)
		(*s)->delta_y =0;
	else if (key_code == D)
		(*s)->delta_x = 0;
	else if (key_code == 123)
		(*s)->turn_dirct = 0;
	else if (key_code == 124)
		(*s)->turn_dirct = 0;
	// printf("release : %d\n", key_code);
	return (0);
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}


void init_funct(t_struct **s)
{
	(*s)->mlx = mlx_init();
	(*s)->win = mlx_new_window((*s)->mlx, (*s)->win_width, (*s)->win_higth, "CUB3D");
	(*s)->img.img = mlx_new_image((*s)->mlx, (*s)->win_width, (*s)->win_higth);
	(*s)->img.addr = mlx_get_data_addr((*s)->img.img, &((*s)->img.bits_per_pixel), &((*s)->img.line_length),
								&((*s)->img.endian));
}
int wall_collision(double x,double y, t_struct **s)
{
	int xx = floor(x/(*s)->tail_size);
	int yy = floor(y/(*s)->tail_size);
	// printf("%d, %d\n",(*s)->map_rows, (*s)->map_cols);
	if (xx < 0 || xx >= ((*s)->map_cols - 1) || yy < 0 || yy  >= ((*s)->map_rows - 1))
		return (1);
	if (!(*s)->map[yy] || (*s)->map[yy][xx] == 0 || (*s)->map[yy][xx] == '1')
		return(1);
	// printf("y : %d , x: %d" ,yy ,xx);
	return(0);
}

int wall_check(double x,double y, t_struct **s)
{
	int xx = floor((x/(*s)->tail_size));
	int yy = floor((y/(*s)->tail_size));
	if (xx < 0 || xx >= ((*s)->map_cols) || yy < 0 || yy  >= ((*s)->map_rows) )
		return (1);
	if ((*s)->map[yy][xx] == '1')
		return(1);
	return(0);
}
int update_info ( t_struct **s)
{
	(*s)->rot_angle += (*s)->turn_dirct * (*s)->rot_speed; 
	norm(s);
	double x_steps = (*s)->delta_x*(*s)->move_speed;
	double y_steps = (*s)->delta_y*(*s)->move_speed;
	(*s)->real_x = (*s)->player_x + (y_steps * cos((*s)->rot_angle));
	(*s)->real_y = (*s)->player_y + (y_steps * sin((*s)->rot_angle));
	if (wall_collision((*s)->real_x,(*s)->real_y, s) == 0)
	{
		// printf("###################################\n");
		(*s)->player_x = (*s)->real_x;
		(*s)->player_y = (*s)->real_y;
	}
	(*s)->real_x = (*s)->player_x - (x_steps * (sin((*s)->rot_angle)));
	(*s)->real_y = (*s)->player_y + (x_steps * (cos((*s)->rot_angle)));
	if (wall_collision((*s)->real_x,(*s)->real_y, s) == 0)
	{
		// printf("**********************************\n");
		(*s)->player_x = (*s)->real_x;
		(*s)->player_y = (*s)->real_y;
	}
	// printf("%f , %f\n", (*s)->player_x, (*s)->player_y);
	mlx_clear_window((*s)->mlx, (*s)->win);
	put_(s);
	return(0);
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
void    draw_line_dda(t_data *img, double beginX, double beginY, double endX, double endY, double colorw)
{
    int        d[2];
    int        i;
    int        step;
    float    x[2];
    float    inc[2];

    i = 0;
	d[0] = endX - beginX;
     d[1] = endY - beginY;
    if (abs(d[0]) > abs(d[1]))
        step = abs(d[0]);
    else
        step = abs(d[1]);
    inc[0] = (float)d[0] / (float)step;
    inc[1] = (float)d[1] / (float)step;
    x[0] = beginX;
    x[1] = beginY;
    while (i < step /*&& x[0] <= 128 && x[1] <= 128*/)
    {
        my_mlx_pixel_put(img, floor(x[0]), floor(x[1]), 0xeb4034);
        x[0] += inc[0];
        x[1] += inc[1];
        i++;
    }
}
void draw_line_dda2(t_data *img, double beginX, double beginY, double endX, double endY, double color) {
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

double distance (double xb, double yb, double xe, double ye)
{
	return (sqrt((xe-xb)*(xe-xb)+(ye-yb)*(ye-yb)));
}

t_ray fill_info(t_inter r1, t_ray ray, int vert)
{
	
	ray.distance = r1.dist;
	ray.hit_x = r1.x;
	ray.hit_y = r1.y;
	ray.hit_vertical = vert;
	return (ray);
}
t_inter h_intersect (t_ray ray, t_struct **s)
{
	t_inter interh;
	int found_h_wall = 0;
	double h_dist = 1e30;
	double h_x = 0;
	double h_y = 0;
	double x_intercept = 0;
	double y_intercept = 0;
	double y_step;
	double x_step;
	double next_x;
	double next_y;
	int h_content = 0;

	y_intercept = floor ((*s)->player_y / (*s)->tail_size)*(*s)->tail_size;
	if (ray.facing_down)
	{
		y_intercept += (*s)->tail_size;
		
	}
	x_intercept = (*s)->player_x + (double)(y_intercept - (*s)->player_y) / (double)tan(ray.ray_angle);
	y_step = (*s)->tail_size;
	if (ray.facing_up)
		y_step*=(-1);
	x_step = y_step/(double)tan(ray.ray_angle);
	if (ray.facing_left && x_step > 0)
		x_step*=(-1);
	if(ray.facing_right && x_step < 0)
		x_step*= (-1);
	next_x = x_intercept;
	next_y = y_intercept;
	while (((int)(next_x /(*s)->tail_size) >= 0)
		&& ((int)(next_x /(*s)->tail_size) < (*s)->map_cols) 
		   && ((int)(next_y / (*s)->tail_size) >= 0 ) 
			&& (int) (next_y / (*s)->tail_size) < (*s)->map_rows)
	{
		double x_check= next_x;
		double y_check = next_y;
		if(ray.facing_up)
			y_check--;
		if (wall_check(x_check, y_check, s) == 1)
		{
			h_x = next_x;
			h_y = next_y;
			found_h_wall = 1;
			h_content = (*s)->map[(int)floor(y_check / (*s)->tail_size)][ (int)floor(x_check / (*s)->tail_size)];
			h_dist = distance ((*s)->player_x, (*s)->player_y, h_x, h_y);
			// ray = fill_info(h_x , h_y , h_dist , h_content, angle);
			interh.x = h_x;
			interh.y = h_y;
			interh.dist = h_dist;
			interh.hit_h = true;
			return (interh);
		}
		else
		{
			interh.hit_h = false;
			next_x += x_step;
			next_y += y_step;
		}
	}
	interh.x = next_x;
	interh.y = next_y;
	interh.dist = distance ((*s)->player_x, (*s)->player_y, interh.x, interh.y);
	return (interh);
}

t_inter v_intersect (t_ray ray, t_struct **s)
{
	t_inter interv;
	int found_v_wall = 0;
	double v_distd = 1e30;
	double v_x = 0;
	double v_y = 0;
	double x_intercept = 0;
	double y_intercept = 0;
	double y_step;
	double x_step;
	double next_x;
	double next_y;
	int v_content = 0;

	x_intercept = floor ((*s)->player_x/(*s)->tail_size)*(*s)->tail_size;
	if (ray.facing_right)
		x_intercept += (*s)->tail_size;
	y_intercept = (*s)->player_y+(double)(x_intercept - (*s)->player_x)*(double)tan(ray.ray_angle);
	x_step = (*s)->tail_size;
	if (ray.facing_left)
		x_step*=(-1);
	y_step = x_step*(double)tan(ray.ray_angle);
	if (ray.facing_up && y_step > 0)
		y_step*=(-1);
	if(ray.facing_down && y_step < 0)
		y_step*= (-1);
	next_x = x_intercept;
	next_y = y_intercept;
	while (((int)(next_x /(*s)->tail_size) >= 0)
		&& ((int)(next_x /(*s)->tail_size) < (*s)->map_cols) 
		   && ((int)(next_y / (*s)->tail_size) >= 0 ) 
			&& (int) (next_y / (*s)->tail_size) < (*s)->map_rows)
	{
		double x_check = next_x;
		if(ray.facing_left)
			x_check--;
		double y_check = next_y;
		if (wall_check(x_check, y_check, s) == 1)
		{
			v_x = next_x;
			v_y = next_y;
			found_v_wall = 1;
			// v_content = (*s)->map[(int)floor(y_check / (*s)->tail_size)][ (int)floor(x_check / (*s)->tail_size)];
			v_distd = distance ((*s)->player_x, (*s)->player_y, v_x, v_y);
			interv.x = v_x;
			interv.y = v_y;
			interv.dist = v_distd;
			interv.hit_v = true;
			return (interv);
		}
		else
		{
			interv.hit_v = false;
			next_x += x_step;
			next_y += y_step;
		}
	}
	interv.x = next_x;//
	interv.y = next_y;//
	interv.dist = distance ((*s)->player_x, (*s)->player_y, interv.x, interv.y);
	return(interv);
}
t_ray is_facing(t_ray ray)
{
	if (ray.ray_angle  > 0 && ray.ray_angle < M_PI)
		ray.facing_down = 1;
	else
		ray.facing_down = 0;
	ray.facing_up = !ray.facing_down;
	if (ray.ray_angle  < (0.5*M_PI) || ray.ray_angle > (1.5*M_PI))
		ray.facing_right = 1;
	else
		ray.facing_right = 0;
	ray.facing_left = !ray.facing_right;
	return(ray);
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
void cast_rays(t_struct **s)
{
	int i = 0;
	double ray_ang = (*s)->rot_angle - ((*s)->fov_angle / 2);
	(*s)->rays = malloc(sizeof (t_ray));

	while (i < (*s)->num_rays)
	{
		(*s)->rays->ray_angle = normalize(ray_ang);
		*(*s)->rays = is_facing(*(*s)->rays);
		t_inter r1 =  v_intersect(*(*s)->rays , s);
		//printf("-%f %f\n", r1.x, r1.y);
		// exit(1);
		t_inter r2 = h_intersect(*(*s)->rays , s);
		//printf("--%f %f\n", r2.x, r2.y);
		//printf("%f, %f\n",r1.dist, r2.dist);
		// exit(1);
		if (r1.dist <= r2.dist )
		{
			*(*s)->rays = fill_info(r1, *(*s)->rays,1);
			// my_mlx_pixel_put(&(*s)->img, round(((*s)->player_x + r1.dist * cos(ray_ang)) * MINI), round(((*s)->player_y + r1.dist * sin(ray_ang)) * MINI), 0x00ff00);
			// drawingray(*(*s)->rays,s);
		if (i == (*s)->num_rays/2)
			draw_line_dda(&(*s)->img, (*s)->player_x + 32 , (*s)->player_y + 32 , (*s)->rays->hit_x, (*s)->rays->hit_y, 0x00ff00);
		}
		else
		{
			*(*s)->rays = fill_info(r2, *(*s)->rays,0);
		if (i == (*s)->num_rays/2)
			draw_line_dda(&(*s)->img, (*s)->player_x + 32 , (*s)->player_y +32 , (*s)->rays->hit_x, (*s)->rays->hit_y, 0xff0000);
			// my_mlx_pixel_put(&(*s)->img, round(((*s)->player_x +  r2.dist * cos(ray_ang)) * MINI), round(((*s)->player_y + (r2.dist * sin(ray_ang))) * MINI), 0x0ff0000);
			// drawingray(*(*s)->rays,s);
		}
		// draw_rays(s, (*s)->rot_angle);
		// render_walls(s, i, 0, (*s)->rays);
		i++;
		ray_ang += ((*s)->fov_angle / (double)(*s)->num_rays);
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
	// push_rays(s);
	int j =0;
	int i =0;
	int k =0;
	int l= 0;
		k = 0;

	while ((*s)->map[k])
	{
		l = 0;
		while ((*s)->map[k][l])
		{
			i = 0;
			while (i < 63)
			{
				j = 0;
				while (j < 63)
				{
					if ((*s)->map[k][l] == '1')
						my_mlx_pixel_put(&((*s)->img), ((l*(*s)->tail_size)+j) * MINI, ((k*(*s)->tail_size)+i )* MINI, 0x2c446d);
					else if ((*s)->map[k][l] == '0' || ft_strchrr("NSWE", (*s)->map[k][l]) == 1)
							my_mlx_pixel_put(&((*s)->img), ((l*(*s)->tail_size)+j) * MINI, ((k*(*s)->tail_size)+i) * MINI, 0xece7dd);
					j++;
				}
				i++;
			}
			l++;
		}
		k++;
	}
	draw_disk(s);
	cast_rays(s);
	draw_rays(s);
	// for (int i = 0; i < (*s)->num_rays; i++)
	// {
		
	// }
	mlx_put_image_to_window((*s)->mlx,(*s)->win, (*s)->img.img, 0, 0);
}
int key_exit(int key_code, t_info *info)
{
	(void)info;
	if (key_code == 17)
		exit(0);
	return(0);
}

void manage_events(t_struct **s)
{
	mlx_hook((*s)->win, 3, 0, key_released, (s));
	mlx_hook((*s)->win, 2, 0, key_pressed, (s));
	mlx_hook((*s)->win, 17, 0, key_exit, (s));
	mlx_loop_hook((*s)->mlx, &update_info, (s));
}

void    put_pixels(t_struct **s)
{
	init_funct(s);
	manage_events(s);
}
