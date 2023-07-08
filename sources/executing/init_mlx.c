/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:11:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/07/08 18:36:39 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// #include "../../includes/thomas.h"

double	get_angle(double angle, int rotation)
{
	angle += rotation;
	if (angle > 359)
		angle -= 360;
	else if (angle < 0)
		angle += 360;
	return (angle);
}

static int	check_keycode(int keycode, t_cub *cub)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_fov_x;

	rot_speed = 0.1;
	old_dir_x = cub->p->dir.x;
	old_fov_x = cub->p->fov.x;
	if (keycode == ESC)
		exit_cub(cub);
	// if (keycode == W)
	// 	move_player(cub, cub->p->pos.coef_ns, 1);
	// if (keycode == S)
	// 	move_player(cub, cub->p->pos.coef_ns, -1);
	// if (keycode == A)
	// 	move_player(cub, cub->p->pos.coef_we, 1);
	// if (keycode == D)
	// 	move_player(cub, cub->p->pos.coef_we, -1);
	if (keycode == L_ARROW)
	{
		cub->p->pos.angle = get_angle(cub->p->pos.angle, -SPEED_ANGLE);

		cub->p->dir.x = cub->p->dir.x * cos(-rot_speed) - cub->p->dir.y * sin(-rot_speed);
		cub->p->dir.y = old_dir_x * sin(-rot_speed) + cub->p->dir.y * cos(-rot_speed);
		cub->p->fov.x = cub->p->fov.x * cos(-rot_speed) - cub->p->fov.y * sin(-rot_speed);
		cub->p->fov.y = old_fov_x * sin(-rot_speed) + cub->p->fov.y * cos(-rot_speed);

		// move_player(cub, cub->p->pos.coef_ns, 0);
	}
	if (keycode == R_ARROW)
	{
		cub->p->pos.angle = get_angle(cub->p->pos.angle, SPEED_ANGLE);

		cub->p->dir.x = cub->p->dir.x * cos(rot_speed) - cub->p->dir.y * sin(rot_speed);
		cub->p->dir.y = old_dir_x * sin(rot_speed) + cub->p->dir.y * cos(rot_speed);
		cub->p->fov.x = cub->p->fov.x * cos(rot_speed) - cub->p->fov.y * sin(rot_speed);
		cub->p->fov.y = old_fov_x * sin(rot_speed) + cub->p->fov.y * cos(rot_speed);

		// move_player(cub, cub->p->pos.coef_ns, 0);
	}
	// printf("dirX %f  dirY %f  ", cub->p->dir.x, cub->p->dir.y);
	// printf("planeX %f  planeY %f\n", cub->p->fov.x, cub->p->fov.y);
	if (keycode == M)
	{
		if (cub->imgs->show_mini)
		{
			mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->minimap.img, 0, 0);
			cub->imgs->show_mini = 0;
		}
		else
		{
			cub->imgs->show_mini = 1;
			render_cub3d(cub);
		}
	}
	return (1);
}

void	init_image(t_cub *cub)
{
	cub->imgs->game.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->imgs->game.addr = mlx_get_data_addr(cub->imgs->game.img, \
	&cub->imgs->game.bits_per_pixel, &cub->imgs->game.line_length, \
	&cub->imgs->game.endian);
	cub->imgs->minimap.img = mlx_new_image(cub->mlx, cub->map->width * \
	GRID_MINI, cub->map->height * GRID_MINI);
	cub->imgs->minimap.addr = mlx_get_data_addr(cub->imgs->minimap.img, \
	&cub->imgs->minimap.bits_per_pixel, &cub->imgs->minimap.line_length, \
	&cub->imgs->minimap.endian);
}

// int	init_mlx(t_cub *cub)
// {
	// cub->mlx = mlx_init();
	// cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	// cub->imgs = malloc(sizeof(t_imgs));
	// if (!cub->imgs)
	// 	return (-1);
	// if (parse_xpm(cub) != 0)
	// 	return (exit_cub(cub), -1);
	// init_image(cub);
	// mlx_hook(cub->win, 2, 1L << 0, check_keycode, cub);
	// mlx_hook(cub->win, 17, 1L << 0, exit_cub, cub);
	// mlx_loop_hook(cub->mlx, render_cub3d, cub);
	// mlx_loop(cub->mlx);
	// return (0);
// }















#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define texWidth 128
#define texHeight 128
// #define texWidth 256
// #define texHeight 256
#define mapWidth 24
#define mapHeight 24
// #define width 1280
// #define height 720

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	t_img	img;
	int		buf[(int)WIN_HEIGHT][(int)WIN_WIDTH];
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;
}				t_info;


void	calc(t_cub *cub)
{
	for(int x = 0; x < WIN_WIDTH; x++)
	{
		double cameraX = 2 * x / WIN_WIDTH - 1;
		cub->p->ray[x]->dir.x = cub->p->dir.x + cub->p->fov.x * cameraX;
		cub->p->ray[x]->dir.y = cub->p->dir.y + cub->p->fov.y * cameraX;

		int mapX = (int)cub->p->pos_3d.x;
		int mapY = (int)cub->p->pos_3d.y;

		// //length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		//  //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / cub->p->ray[x]->dir.x);
		double deltaDistY = fabs(1 / cub->p->ray[x]->dir.y);
		double perpWallDist;
		
		// //what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0;
		int side;

		if (cub->p->ray[x]->dir.x < 0)
		{
			stepX = -1;
			sideDistX = (cub->p->pos_3d.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->p->pos_3d.x) * deltaDistX;
		}
		if (cub->p->ray[x]->dir.y < 0)
		{
			stepY = -1;
			sideDistY = (cub->p->pos_3d.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->p->pos_3d.y) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (cub->map->array[mapX][mapY] == '1')
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - cub->p->pos_3d.x + (1 - stepX) / 2) / cub->p->ray[x]->dir.x;
		else
			perpWallDist = (mapY - cub->p->pos_3d.y + (1 - stepY) / 2) / cub->p->ray[x]->dir.y;


		// //Calculate height of line to draw on screen
		// int lineHeight = (int)(height / perpWallDist);
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		// //calculate lowest and highest pixel to fill in current stripe
		// int drawStart = -lineHeight / 2 + height / 2;
		// if(drawStart < 0)
		// 	drawStart = 0;
		// int drawEnd = lineHeight / 2 + height / 2;
		// if(drawEnd >= height)
		// 	drawEnd = height - 1;
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if(drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		// // texturing calculations
		// int texNum = worldMap[mapX][mapY] - 1;
		// int texNum = worldMap[mapX][mapY] - 1;
		// (void)texNum;

		// // calculate value of wallX
		// double wallX;
		// if (side == 0)
		// 	wallX = info->posY + perpWallDist * rayDirY;
		// else
		// 	wallX = info->posX + perpWallDist * rayDirX;
		// wallX -= floor(wallX);
		double wallX;
		if (side == 0)
			wallX = cub->p->pos_3d.y + perpWallDist * cub->p->ray[x]->dir.y;
		else
			wallX = cub->p->pos_3d.x + perpWallDist * cub->p->ray[x]->dir.x;
		wallX -= floor(wallX);

		// // x coordinate on the texture
		// int texX = (int)(wallX * (double)texWidth);
		// if (side == 0 && rayDirX > 0)
		// 	texX = texWidth - texX - 1;
		// if (side == 1 && rayDirY < 0)
		// 	texX = texWidth - texX - 1;
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && cub->p->ray[x]->dir.x > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && cub->p->ray[x]->dir.y < 0)
			texX = texWidth - texX - 1;

		// // How much to increase the texture coordinate perscreen pixel
		// double step = 1.0 * texHeight / lineHeight;
		double step = 1.0 * texHeight / lineHeight;

		// // Starting texture coordinate
		// double texPos = (drawStart - height / 2 + lineHeight / 2) * step;
		double texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step;

		// for (int y = drawStart; y < drawEnd; y++)
		// {
		// 	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		// 	int texY = (int)texPos & (texHeight - 1);
		// 	texPos += step;

		// 	int color = info->texture[texNum][texHeight * texY + texX];

		// 	info->buf[y][x] = color;
		// }
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;

			int color = cub->north.px[cub->north.height * texY + texX];

			put_pixel(&cub->imgs->game, x, y, color);
		}

		if (drawEnd < 0)
			drawEnd = WIN_HEIGHT; //becomes < 0 when the integer overflows

		int i = drawEnd;
		while (++i < WIN_HEIGHT)
		{
			// put_pixel(&cub->imgs->game, (int)WIN_WIDTH - x, i, cub->floor);
			// put_pixel(&cub->imgs->game, (int)WIN_WIDTH - x, (int)WIN_HEIGHT - i, cub->roof);
			put_pixel(&cub->imgs->game, x, i, cub->floor);
			put_pixel(&cub->imgs->game, x, (int)WIN_HEIGHT - i, cub->roof);
		}
	}
}



void	draw_player_body(t_cub *cub)
{
	int			angle;
	int			i;
	t_vector	start;
	t_vector	coef;

	angle = -1;
	while (++angle < 360)
	{
		start.x = cub->p->pos.start.x;
		start.y = cub->p->pos.start.y;
		coef.x = sin(angle * M_PI / 180);
		coef.y = -cos(angle * M_PI / 180);
		i = -1;
		while (++i < GRID_MINI / 3)
		{
			if (start.x > 0 && start.y > 0)
				put_pixel(&cub->imgs->minimap, start.x + GRID_MINI / 2, start.y + GRID_MINI / 2, 0x0082180e);
			else
				break ;
			start.x += coef.x;
			start.y += coef.y;
		}
	}
}

void	draw_until_wall(t_cub *cub, t_ray *ray, t_vector coef, int sign)
{
	t_vector	tmp;

	tmp.x = ray->start.x;
	tmp.y = ray->start.y + (double)GRID_MINI / 2;
	while (1)
	{
		if (tmp.x > 0 && tmp.y > 0)
		{
			if (!put_pixel(&cub->imgs->minimap, tmp.x + GRID_MINI / 2, tmp.y - 1, 0x00ff1500))
				break ;
		}
		else
			break ;
		tmp.x += (coef.x) * sign;
		tmp.y += (coef.y) * sign;
	}
}

void	draw_ray(t_cub *cub, t_vector coef, int sign)
{
	t_vector	tmp;

	tmp.x = cub->p->pos.start.x;
	tmp.y = cub->p->pos.start.y + (double)GRID_MINI / 2;
	while (1)
	{
		if (tmp.x > 0 && tmp.y > 0)
		{
			if (!put_pixel(&cub->imgs->minimap, tmp.x + GRID_MINI / 2, tmp.y - 1, 0x00ff1500))
			{
				// cub->p->ray[i]->wall.x = tmp.x; // tests
				// cub->p->ray[i]->wall.y = tmp.y; // tests
				break ;
			}
		}
		else
			break ;
		tmp.x += (coef.x) * sign;
		tmp.y += (coef.y) * sign;
	}
}

void	draw_fov(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
		draw_ray(cub, cub->p->ray[i]->coef_ns, 1);
}

void	generate_player(t_cub *cub)
{
	draw_player_body(cub);
	draw_fov(cub);
}

int	main_loop(t_cub *cub)
{
	generate_minimap(cub);
	calcul_coef(cub);
	// generate_player(cub);
	calc(cub);
	// draw(info);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->game.img, 0, 0);
	// mlx_put_image_to_window(cub->mlx, cub->win, cub->imgs->minimap.img, 0, 0);
	return (0);
}

int	key_press(int key, t_cub *cub)
{
	if (key == W)
	{
		// move_player(cub, cub->p->pos.coef_ns, 1); // old move forward
		move_player(cub, cub->p->dir, NS, 1);
	}
	if (key == S)
	{
		// move_player(cub, cub->p->pos.coef_ns, -1); // old move left
		move_player(cub, cub->p->dir, NS, -1);
	}
	if (key == D)
	{
		// move_player(cub, cub->p->pos.coef_we, -1); // old move right
		move_player(cub, cub->p->pos.coef_ns, EW, 1);
	}
	if (key == A)
	{
		// move_player(cub, cub->p->pos.coef_we, 1); // old move left
		move_player(cub, cub->p->pos.coef_ns, EW, -1);
	}
	if (key == R_ARROW)
	{
		cub->p->pos.angle = get_angle(cub->p->pos.angle, 4.0);

		double oldDirX = cub->p->dir.x;
		cub->p->dir.x = cub->p->dir.x * cub->cos_angle - cub->p->dir.y * -cub->sin_angle;
		cub->p->dir.y = oldDirX * -cub->sin_angle + cub->p->dir.y * cub->cos_angle;
		double oldPlaneX = cub->p->fov.x;
		cub->p->fov.x = cub->p->fov.x * cub->cos_angle - cub->p->fov.y * -cub->sin_angle;
		cub->p->fov.y = oldPlaneX * -cub->sin_angle + cub->p->fov.y * cub->cos_angle;

		move_player(cub, cub->p->dir, 0, 0);
	}
	if (key == L_ARROW)
	{
		cub->p->pos.angle = get_angle(cub->p->pos.angle, -4.0);
		
		double oldDirX = cub->p->dir.x;
		cub->p->dir.x = cub->p->dir.x * cub->cos_angle - cub->p->dir.y * cub->sin_angle;
		cub->p->dir.y = oldDirX * cub->sin_angle + cub->p->dir.y * cub->cos_angle;
		double oldPlaneX = cub->p->fov.x;
		cub->p->fov.x = cub->p->fov.x * cub->cos_angle - cub->p->fov.y * cub->sin_angle;
		cub->p->fov.y = oldPlaneX * cub->sin_angle + cub->p->fov.y * cub->cos_angle;

		move_player(cub, cub->p->dir, 0, 0);
	}
	if (key == ESC)
		exit(0);
	return (0);
}

int	exit_cub3d(t_cub *cub)
{
	(void)cub;
	exit (0);
}

int	init_mlx(t_cub *cub)
{
	(void)cub;
	(void)check_keycode;

	cub->mlx = mlx_init();
	cub->imgs = malloc(sizeof(t_imgs));
	if (!cub->imgs)
		return (-1);
	if (parse_xpm(cub) != 0)
		return (exit_cub(cub), -1);
	init_image(cub);

	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");

	main_loop(cub);

	mlx_hook(cub->win, 2, 1l << 0, key_press, cub);
	mlx_hook(cub->win, 17, 1l << 0, exit_cub3d, cub);
	mlx_loop_hook(cub->mlx, &main_loop, cub);

	mlx_loop(cub->mlx);
	return (0);
}
