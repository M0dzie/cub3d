
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

// double	draw_ray(t_cub *cub, double ray_angle, int i)
// {
// 	double		distance = 0;
// 	double		r_cos;
// 	double		r_sin;
// 	t_vector	tmp;

// 	// tmp.x = cub->p->pos.start.x;
// 	// tmp.y = cub->p->pos.start.y + (double)GRID_MINI / 2;
// 	tmp.x = cub->p->pos.start.x + 0.5;
// 	tmp.y = cub->p->pos.start.y + 0.5;
// 	r_cos = cos(get_radian(ray_angle)) / 50;
// 	r_sin = sin(get_radian(ray_angle)) / 50;
// 	while (1)
// 	{
// 		if (tmp.x > 0 && tmp.y > 0)
// 		{
// 			if (!put_pixel(&cub->imgs->minimap, tmp.x + GRID_MINI / 2, tmp.y - 1, 0x00ff1500))
// 			{
// 				cub->p->ray[i]->wall.x = tmp.x; // tests
// 				cub->p->ray[i]->wall.y = tmp.y; // tests
// 				break ;
// 			}
// 		}
// 		else
// 			break ;
// 		tmp.x += r_cos;
// 		tmp.y += r_sin;
// 	}
// 	distance = sqrt(powf(cub->p->ray[i]->wall.x - cub->p->pos.start.x - 0.5, 2.0) + \
// 	powf(cub->p->ray[i]->wall.y - cub->p->pos.start.y - 0.5, 2.0));
// 	return (distance * cos(get_radian(ray_angle - cub->p->ray[i]->angle)));
// }

// void	draw_fov(t_cub *cub)
// {
// 	double	inc_angle = FOV - WIN_WIDTH;
// 	double	distance = 0;
// 	double	ray_angle = cub->p->pos.angle - (FOV / 2);
// 	int		ray_count = -1;

// 	while (++ray_count < WIN_WIDTH)
// 	{
// 		distance = draw_ray(cub, ray_angle, ray_count);
// 		cub->p->ray[ray_count]->dist = distance;
// 		ray_angle += inc_angle;
// 	}
// }

// static void	draw_wall(t_data *background, t_vector top_left, t_vector bottom_right, int color)
// {
// 	while (top_left.x < bottom_right.x + 1)
// 	{
// 		while (top_left.y > bottom_right.y)
// 		{
// 			put_pixel(background, top_left.x, top_left.y, color);
// 			top_left.y--;
// 		}
// 		top_left.x++;
// 	}
// }

// void	generate_3d(t_cub *cub)
// {
// 	t_vector	top_left;
// 	t_vector	bottom_right;
// 	double		wall_height;
// 	int			i;

// 	if (cub->imgs->back.img)
// 		mlx_destroy_image(cub->mlx, cub->imgs->back.img);
// 	cub->imgs->back.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	cub->imgs->back.addr = mlx_get_data_addr(cub->imgs->back.img, &cub->imgs->back.bits_per_pixel, &cub->imgs->back.line_length, &cub->imgs->back.endian);
// 	put_floor_and_ceiling(cub);
// 	i = -1;
// 	while (cub->p->ray[++i])
// 	{
// 		cub->p->ray[i]->dist = fix_fisheye(cub, cub->p->ray[i]->dist, i);
// 		wall_height = 1.0 / cub->p->ray[i]->dist;
// 		wall_height = wall_height * WIN_HEIGHT;
// 		wall_height *= 14;
// 		top_left.x = i / 1; // 1 = wall_width
// 		top_left.y = WIN_HEIGHT / 2 + wall_height / 2;
// 		bottom_right.x = i * 1 + 1;
// 		bottom_right.y = WIN_HEIGHT / 2 - wall_height / 2;
// 		draw_wall(&cub->imgs->back, top_left, bottom_right, 0x413C37);
// 	}
// }

// static void	init_data_raycaster(t_cub *cub, t_raycaster *ray, int i)
// {
// 	ray->dist.x = sqrt(1 + powf(cub->p->ray[i]->dir.y, 2.0) / \
// 	powf(cub->p->ray[i]->dir.x, 2.0));
// 	ray->dist.y = sqrt(1 + powf(cub->p->ray[i]->dir.x, 2.0) / \
// 	powf(cub->p->ray[i]->dir.y, 2.0));
// 	ray->hit = 0;
// 	ray->side = 0;
// 	ray->map.x = cub->p->pos.start.x / GRID_MINI;
// 	ray->map.y = cub->p->pos.start.y / GRID_MINI;
// 	if (cub->p->ray[i]->dir.x < 0)
// 	{
// 		ray->step.x = -1;
// 		ray->next.x = (cub->p->pos.start.x - ray->map.x) * ray->dist.x;
// 	}
// 	else
// 	{
// 		ray->step.x = 1;
// 		ray->next.x = (ray->map.x + 1 - cub->p->pos.start.x) * ray->dist.x;
// 	}
// 	if (cub->p->ray[i]->dir.y < 0)
// 	{
// 		ray->step.y = -1;
// 		ray->next.y = (cub->p->pos.start.y - ray->map.y) * ray->dist.y;
// 	}
// 	else
// 	{
// 		ray->step.y = 1;
// 		ray->next.y = (ray->map.y + 1 - cub->p->pos.start.y) * ray->dist.y;
// 	}
// }

// void	get_next_wall(t_cub *cub, int i)
// {
// 	t_raycaster	ray;

// 	init_data_raycaster(cub, &ray, i);
// 	while (!ray.hit)
// 	{
// 		if (ray.next.x < ray.next.y)
// 		{
// 			ray.next.x += ray.dist.x;
// 			ray.map.x += ray.step.x;
// 			ray.side = 0;
// 		}
// 		else
// 		{
// 			ray.next.y += ray.dist.y;
// 			ray.map.y += ray.step.y;
// 			ray.side = 1;
// 		}
// 		if (cub->map->array[(int)ray.map.y][(int)ray.map.x] == \
// 		'1')
// 			ray.hit = 1;
// 	}
// 	if (ray.side == 0)
// 		cub->p->ray[i]->dist = ray.next.x - ray.dist.x;
// 	else
// 		cub->p->ray[i]->dist = ray.next.y - ray.dist.y;
// 	if (cub->p->ray[i]->dist < 0)
// 		cub->p->ray[i]->dist *= -1;
// 	// printf("dist = %lf\n", cub->p->ray[i]->dist);
// }


// double	adjust_distance(double start_x, double start_y, t_vector wall)
// {
// 	return (sqrt(pow(wall.x - start_x, 2.0) + pow(wall.y - start_y, 2.0)));
// }

// double	find_wall_distance(t_cub *cub, t_vector p_pos, double angle, int column)
// {
// 	t_vector	ray;
// 	double		a_ray;
// 	double		distance;
// 	double		step;

// 	ray.x = p_pos.x / GRID_MINI;
// 	ray.y = p_pos.y / GRID_MINI;
// 	distance = 0;
// 	step = 0.1;
// 	a_ray = angle - FOV / 2 + (double)column / WIN_WIDTH * FOV;
// 	// printf("angle ray = %lf\n", a_ray);
// 	while (1)
// 	{
// 		ray.x += step * cos(get_radian(a_ray));
// 		ray.y += step * sin(get_radian(a_ray));
// 		printf("ray.x = %lf and ray.y = %lf\n", ray.x, ray.y);
// 		// if (ray.x < 0 || ray.y < 0)
// 		// 	break ;
// 		if (cub->map->array[(int)ray.y][(int)ray.x] == '1')
// 		{
// 			distance = adjust_distance(p_pos.x / GRID_MINI, p_pos.y / GRID_MINI, ray) * 30;
// 			break ;
// 		}
// 	}
// 	// printf("player.x = %d and player.y = %d\n", (int)cub->p->pos.start.x / GRID_MINI, (int)cub->p->pos.start.y / GRID_MINI);
// 	// printf("find wall, x= %d and y= %d\n", (int)ray.x, (int)ray.y);
// 	// printf("distance = %.2lf\n", distance);
// 	return (distance);
// } 
