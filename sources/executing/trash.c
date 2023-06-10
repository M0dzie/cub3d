
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

// void	init_camera_plane(t_cub *cub)
// {
// 	t_vector	tmp_coef;
// 	t_vector	tmp_pos;
// 	t_vector	tmp;
// 	double		inc;
// 	int			distance;
// 	int			i;

// 	i = -1;
// 	inc = H_FOV / WIN_WIDTH;
// 	tmp_coef.x = cub->p->pos.coef_we.x * ((WIN_WIDTH / 2) / H_FOV);
// 	tmp_coef.y = cub->p->pos.coef_we.y * ((WIN_WIDTH / 2) / H_FOV);
// 	tmp_pos.x = cub->p->pos.start.x + tmp_coef.x;
// 	tmp_pos.y = cub->p->pos.start.y + tmp_coef.y;
// 	cub->p->new_ray = ft_calloc(WIN_WIDTH + 1, sizeof(t_ray_map *));
// 	if (!cub->p->new_ray)
// 		return ((void)display_error("cub->p->new_ray", 4));
// 	while (++i < WIN_WIDTH)
// 	{
// 		tmp.x = tmp_pos.x;
// 		tmp.y = tmp_pos.y + (double)GRID_MINI / 2;
// 		distance = 0;
// 		while (1)
// 		{
// 			if (tmp.x > 0 && tmp.y > 0)
// 			{
// 				if (is_wall(&cub->imgs->minimap, tmp.x + GRID_MINI / 2, tmp.y - 1))
// 					break ;
// 			}
// 			else
// 				break ;
// 			tmp.x += tmp_coef.x;
// 			tmp.y += tmp_coef.y;
// 			distance++;
// 		}
// 		cub->p->new_ray[i]->dist = distance;
// 		printf("test dist = %d\n", cub->p->new_ray[i]->dist);
// 		tmp_pos.x += cub->p->pos.coef_we.x * inc;
// 		tmp_pos.y += cub->p->pos.coef_we.y * inc;
// 	}
// }