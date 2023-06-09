// double	get_radian(double angle)
// {
// 	return (angle * M_PI / 180);
// }

// double	fix_fisheye(t_cub *cub, double distance, int i)
// {
// 	double	new_angle;

// 	new_angle = get_radian(cub->p->ray[i]->angle - cub->p->pos.angle);
// 	if (new_angle >= 2.0 * M_PI)
// 		new_angle -= 2.0 * M_PI;
// 	if (new_angle <= 2.0 * M_PI)
// 		new_angle = 0.0;
// 	distance = distance * cos(new_angle);
// 	return (distance);
// }

// double	calculate_distance(t_cub *cub, int i)
// {
// 	double	distance;

// 	distance = sqrt(powf(cub->p->ray[i]->wall.x - cub->p->pos.start.x, 2.0) + \
// 	powf(cub->p->ray[i]->wall.y - cub->p->pos.start.y, 2.0));
// 	// printf("distance = %lf\n", distance);
// 	// printf("old distance = %d\n", cub->p->ray[i]->dist);
// 	distance = fix_fisheye(cub, distance, i);
// 	return (distance);
// }

// void	generate_background(t_cub *cub)
// {
// 	double	wall_height;
// 	double	distance;
// 	int		margin;
// 	int		x;
// 	int		y;

// 	if (cub->imgs->back.img)
// 		mlx_destroy_image(cub->mlx, cub->imgs->back.img);
// 	cub->imgs->back.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	cub->imgs->back.addr = mlx_get_data_addr(cub->imgs->back.img, &cub->imgs->back.bits_per_pixel, &cub->imgs->back.line_length, &cub->imgs->back.endian);
// 	x = -1;
// 	while (cub->p->ray[++x])
// 	{
// 		// calculate_distance(cub, x);
// 		// wall_height = WALL_H / cub->p->ray[x]->dist * 25;
// 		distance = calculate_distance(cub, x);
// 		wall_height = WALL_H / distance * 25;
// 		// wall_height *= cos((cub->p->ray[x]->angle - cub->p->pos.angle) * (M_PI / 180));
// 		margin = (WIN_HEIGHT - wall_height) / 2;
// 		y = -1;
// 		if (margin > 0)
// 		{
// 			while (++y < margin)
// 				put_pixel(&cub->imgs->back, x, y, 0x191970);
// 			while (y < margin + wall_height - 1)
// 			{
// 				put_pixel(&cub->imgs->back, x, y, 0x413C37);
// 				y++;
// 			}
// 			while (y < WIN_HEIGHT)
// 			{
// 				put_pixel(&cub->imgs->back, x, y, 0x4F4943);
// 				y++;
// 			}
// 		}
// 		else
// 		{
// 			while (++y < WIN_HEIGHT)
// 				put_pixel(&cub->imgs->back, x, y, 0x413C37);
// 		}
// 	}
// }