#include "libft_gfx.h"
#include "fcntl.h"

/*
** mlx_get_data_addr is used as int pointer
** so: (line_bytes / 4) because: (int == 4 bytes)
*/

static void setup(t_program *p, char *title)
{
	if (NULL == (p->mlx = mlx_init()))
		ft_die("MLX failed to initialize.");
	if (NULL == (p->win = mlx_new_window(p->mlx, WIN_WIDTH, WIN_HEIGHT, title)))
		ft_die("MLX failed to create a new window.");
	if (NULL == (p->buffer.ptr = mlx_new_image(p->mlx, WIN_WIDTH, WIN_HEIGHT)))
		ft_die("MLX failed to allocate image buffer.");
	p->buffer.data = (int *)mlx_get_data_addr(p->buffer.ptr,
		&p->buffer.pixel_bits,
		&p->buffer.line_bytes,
		&p->buffer.endian);
	p->buffer.line_bytes /= 4;
	p->size.x = WIN_WIDTH;
	p->size.y = WIN_HEIGHT;
}

int mouse_move(int x, int y, void *param)
{
	t_program *p;

	(void)x;
	(void)y;
	p = param;
	ft_clear_buffer(&p->buffer);
	// printf("\nmouse x%d y%d\n", x,y);

	// t_line test;
	// test.start = VEC2(-10, -10);
	// test.start = VEC2(WIN_WIDTH + 10, WIN_HEIGHT + 10);
	// test.start = VEC2(WIN_WIDTH - x, WIN_HEIGHT - y);
	// test.end = VEC2(x, y);
	// if (ft_clip_line(&test))
	// 	ft_draw_line(p, test.start, test.end, 0xFFFFFF);

	// printf("line start x%.0f y%.0f | end x%.0f y%.0f\n",
	// 	test.start.x, test.start.y, test.end.x, test.end.y);
	printf("draw\n");
	// ft_draw_wall(100, 100);
	ft_draw_line(p, VEC2(10, 10), VEC2(100, 100), 0x00FFFF);
	ft_draw_wall(p, 100, 100, 0xFFFF00);
	mlx_put_image_to_window(p->mlx, p->win, p->buffer.ptr, 0, 0);
	return (TRUE);
}

static char	**parse_map(int fd)
{
	char	**map;
	char	*line;
	int		x;
	int		y;

	map = malloc((100 * sizeof(char *)) + 1);

	y = 0;
	while ((y < 100) && ft_get_next_line(fd, &line))
	{
		x = 0;
		map[y] = line;
		++y;
	}
	map[y] = NULL;

	return (map);
}

static void draw_top_view(t_program *p)
{
	int x, y;

	y = 0;
	while (y < 11)
	{
		x = 0;
		while (p->map[y][x])
		{
			if (p->map[y][x] == ' ')
				ft_draw_box(p, VEC2(x * 10, y * 10), VEC2(10, 10), 0x202020);
			else
				ft_draw_box(p, VEC2(x * 10, y * 10), VEC2(10, 10), 0xFFFFFF);
			++x;
		}
		++y;
	}
	t_xy pos = p->plr.pos;
	t_xy dir = p->plr.dir;
	pos.x *= 10;
	pos.y *= 10;
	dir.x *= 20;
	dir.y *= 20;
	t_circle ring = CIRCLE(pos, 3);
	t_line line = LINE(pos.x, pos.y, pos.x + dir.x, pos.y + dir.y);
	ft_draw_ring(p, &ring, 0xFF0000);
	ft_draw_line(p, line.start, line.end, 0xFFCC00);
}

static t_xy find_wall(char **map, t_xy pos, t_xy dir)
{
	t_xy	length;
	t_xy	ratio;
	// t_xy wall;
	// wall.x = (pos.x + dir.x * i.x) - ((int)pos.x - pos.x);
	// wall.y = (pos.y + dir.y * i.y) - ((int)pos.y - pos.y);
	// printf("\n");
	// printf("pos %f %f | dir %f %f\n", pos.x, pos.y, dir.x, dir.y);
	t_xy end = VEC2(pos.x + dir.x, pos.y + dir.y);

	t_xy spot = pos;
	while (map[(int)spot.y][(int)spot.x] == ' ')
	{
		// printf("\tempty space at map[%d][%d]\t(%c)\n",
		// 	(int)spot.y, (int)spot.x, map[(int)spot.y][(int)spot.x]);
		spot.x += dir.x;
		spot.y += dir.y;
		// printf("\tnext lookup at map[%d][%d]\n",
		// 	(int)spot.y, (int)spot.x);
	}
	// printf("\tfound wall at map[%d][%d] \t(%c)\n",
	// 	(int)spot.y, (int)spot.x, map[(int)spot.y][(int)spot.x]);
	// printf("\tspot x%f y%f\n", spot.x, spot.y);
	// spot.x = (dir.x >= 0 ? floor(spot.x) : ceil(spot.x)) - pos.x;
	// spot.y = (dir.y >= 0 ? floor(spot.y) : ceil(spot.y)) - pos.y;
	double vert_bound = (dir.x >= 0 ? floor(spot.x) : ceil(spot.x));
	double hori_bound = (dir.y >= 0 ? floor(spot.y) : ceil(spot.y));
	t_line los = LINE(pos.x, pos.y, spot.x, spot.y);
	t_clip clip;
	if (dir.y < 0)
	{
		clip.top = vert_bound;
		clip.bottom = pos.y;
	}
	else
	{
		clip.top = pos.y;
		clip.bottom = vert_bound;
	}
	if (dir.x < 0)
	{
		clip.left = hori_bound;
		clip.right = pos.x;
	}
	else
	{
		clip.left = pos.x;
		clip.right = hori_bound;
	}
	ft_clip_line(&los, &clip);
	printf("\n");
	printf("dir.x %f, dir.y%f\n", dir.x, dir.y);
	printf("clip mask: \n\t%f \n%f\t%f \n\t%f\n",
		clip.top, clip.left, clip.right, clip.bottom);

	return (spot);
}

static t_xy vec2_rot(t_xy v, double angle)
{
	return ((t_xy){
		v.x * cos(angle) - v.y * sin(angle),
		v.x * sin(angle) + v.y * cos(angle)
	});
}

static void draw_view(t_program *p)
{
	static double	fov = -(90.0 / 2);
	static double	angle = (90.0 / WIN_WIDTH) * (0.01745329251994329576923690768488612);
	t_xy			wall;
	int				column;
	t_xy			idk;

	printf("draw_view x%f y%f\n", idk.x, idk.y);
	column = 0;

	while (column < WIN_WIDTH)
	{
		// wall = find_wall(p->map, p->plr.pos, p->plr.dir);
		t_xy test = vec2_rot(p->plr.dir, angle * column);
		wall = find_wall(p->map, p->plr.pos, test);
		printf("angle = %f, test = %f %f\n", angle, test.x, test.y);
		// if (column < fov)
		// else
		// 	wall = find_wall(p->map, p->plr.pos,
		// 		VEC2(p->plr.dir.x, idk.y * column));

		double magnitude = sqrt(wall.x * wall.x + wall.y * wall.y);
		// printf("original length %f\n", magnitude);
		magnitude = ft_map(magnitude, RANGE(0, 8), RANGE(0, 1));
		// printf("length %f\n", 1 - magnitude);


		if (column < WIN_WIDTH / 2)
		{
			if (idk.x < 0)
			{
				if (column % 5)
					ft_draw_wall(p, column, 1 - magnitude, 0x800000);
				else
					ft_draw_wall(p, column, 1 - magnitude, 0x0);
			}
			else if (column % 5)
				ft_draw_wall(p, column, 1 - magnitude, 0xAA00AA);
			else
				ft_draw_wall(p, column, 1 - magnitude, 0x0);
		}
		else
		{
			if (idk.y < 0)
			{
				if (column % 5)
					ft_draw_wall(p, column, 1 - magnitude, 0x800000);
				else
					ft_draw_wall(p, column, 1 - magnitude, 0x0);
			}
			else if (column % 5)
				ft_draw_wall(p, column, 1 - magnitude, 0x00AAAA);
			else
				ft_draw_wall(p, column, 1 - magnitude, 0x0);
		}
		++column;
	}
}

int mouse_key(int key, int x, int y, void *param)
{
	t_program *p;
	(void)key;
	(void)x;
	(void)y;

	p = param;
	printf("mouse_key draw\n");
	ft_clear_buffer(&p->buffer);
	// ft_draw_wall(p, 100, 50, 0xFFFF00);
	draw_view(p);
	draw_top_view(p);
	mlx_put_image_to_window(p->mlx, p->win, p->buffer.ptr, 0, 0);
	return (TRUE);
}

int window_close(void *param)
{
	(void)param;
	exit(0);
}

int main()
{
	t_program p;
	int fd; if ((fd = open("testmap.txt", O_RDONLY)))
	{
		p.map = parse_map(fd);
		printf("map_parse done\n");
		p.plr.pos = VEC2(2.5, 2.5);
		// p.plr.dir = VEC2(0.894427, 0.447214);
		// p.plr.dir = VEC2(0.910366, 0.413803);
		p.plr.dir = VEC2(0, 1);
		// p.plr.dir = VEC2(0.707107, -0.707107);
		// p.plr.dir = VEC2(-0.554700, 0.832050);
	}

	setup(&p, "test window");
	printf("test done\n");
	mlx_mouse_hook(p.win, &mouse_key, &p);
	// mlx_hook(p.win, EVENT_MOUSE_MOVE, 0, &mouse_move, &p);
	mlx_hook(p.win, EVENT_CLOSE_WIN, 0, &window_close, &p);
	mlx_loop(p.mlx);
}
