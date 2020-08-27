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
		&p->buffer.bpp,
		&p->buffer.width,
		&p->buffer.endian);
	p->buffer.width /= 4;
	p->size.x = WIN_WIDTH;
	p->size.y = WIN_HEIGHT;
	p->mouse.pos = VEC2(0, 0);
	p->mouse.d = VEC2(0, 0);
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

static t_clip get_boundary(t_xy corner1, t_xy corner2)
{
	t_clip out;

	if (corner1.y <= corner2.y)
	{
		out.top = corner1.y;
		out.bottom = corner2.y;
	}
	else
	{
		out.top = corner2.y;
		out.bottom = corner1.y;
	}
	if (corner1.x <= corner2.x)
	{
		out.left = corner1.x;
		out.right = corner2.x;
	}
	else
	{
		out.left = corner2.x;
		out.right = corner1.x;
	}
	return (out);
}

/*
** To cut the line exactly where the line intersects a wall
** could be done in many ways, most simply by calculating
** each grid index intersection...
** https://www.permadi.com/tutorial/raycast/rayc7.html
**
** But that's no fun. The main idea I'm trying to get working is
** using ft_clip_line and a bounding box around the player and
** the truncated index. Having trouble getting that to work...
*/

static t_xy find_wall(t_program *p, t_xy pos, t_xy dir)
{
	t_xy end = VEC2(pos.x + dir.x, pos.y + dir.y);
	t_xy spot = pos;

	while (p->map[(int)spot.y][(int)spot.x] == ' ')
	{
		spot.x += dir.x;
		spot.y += dir.y;
	}

	double xbound = (dir.x > 0 ? ceil(spot.x) : floor(spot.x));
	xbound = (xbound == 0 ? 1 : xbound);
	double ybound = (dir.y > 0 ? ceil(spot.y) : floor(spot.y));
	ybound = (ybound == 0 ? 1 : ybound);
	ft_put_pixel(p, xbound * 10, ybound * 10, 0xFF0000);

	t_line los = LINE(pos.x, pos.y, spot.x, spot.y);
	t_clip clip;
	t_xy norm = vec2_norm(spot);

	clip = CLIP(0, 0, WIN_WIDTH, WIN_HEIGHT);
	clip = get_boundary(pos, VEC2(xbound, ybound));
	// top-right bottom-left
	// if (norm.x > norm.y && spot.x > pos.x)
	// {
	// 	clip = get_boundary(pos, VEC2(xbound, 0));
	// 	int region = ft_get_region(spot, clip);
	// 	printf("outcodes: %d\n", region);
	// 	ft_draw_line(p, vec2_mul(pos, 10), vec2_mul(spot, 10), 0x80C70039);

	// 	if (region & OUTCODE_RIGHT && !(region & (OUTCODE_TOP|OUTCODE_BOTTOM)))
	// 	{
	// 		spot.x = xbound;
	// 		printf("left\n");
	// 		ft_draw_line(p, vec2_mul(pos, 10), vec2_mul(spot, 10), 0x00FFF7);
	// 	}
	// }
	// else if (spot.x > spot.y && spot.x < pos.x)
	// 	clip = get_boundary(pos, VEC2(xbound, WIN_HEIGHT));
	// bottom-right top-left
	// else if (spot.y > spot.x && spot.x > pos.x)
	// 	clip = get_boundary(pos, VEC2(WIN_WIDTH, ybound));
	// else
	// 	clip = get_boundary(pos, VEC2(0, ybound));
	ft_clip_line(&los, clip);

	// return (VEC2(spot.x - pos.x, spot.y - pos.y));
	return (VEC2(los.end.x - pos.x, los.end.y - pos.y));
}

static t_xy find_wall_old(char **map, t_xy pos, t_xy dir)
{
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
	t_clip clip = get_boundary(pos, VEC2(hori_bound, vert_bound));
	// printf("\nstart : %f %f\tend : %f %f \tindex : %d %d\nclip :\t%f\n%f\t%f\n\t%f\n",
	// 	pos.x, pos.y, spot.x, spot.y, (int)spot.x, (int)spot.y,
	// 	clip.top, clip.left, clip.right, clip.bottom);
	ft_clip_line(&los, clip);
	// printf("\n");
	// printf("dir.x %f, dir.y%f\n", dir.x, dir.y);
	// printf("clip mask: \n\t%f \n%f\t%f \n\t%f\n",
	// 	clip.top, clip.left, clip.right, clip.bottom);

	// printf("\t\t\t\t\t\t\t\tlos start %f %f end %f %f\n",
	// 	los.start.x, los.start.y, los.end.x, los.end.y);
	// printf("\t\t\t\t\t\t\t\treturning <%f %f>\n",
	// 	los.end.x - pos.x, los.end.y - pos.y);

	return (VEC2(spot.x - pos.x, spot.y - pos.y));
}

void draw_top_view(t_program *p, t_xy pos, t_xy dir)
{
	int x, y;

	y = 0;
	while (y < 11)
	{
		x = 0;
		while (p->map[y][x])
		{
			if (p->map[y][x] == ' ')
				ft_draw_box(p, VEC2(x * 10, y * 10), VEC2(10, 10), 0xC0202020);
			else
				ft_draw_box(p, VEC2(x * 10, y * 10), VEC2(10, 10), 0xC0FFFFFF);
			++x;
		}
		++y;
	}
	pos.x *= 10;
	pos.y *= 10;
	dir.x *= 20;
	dir.y *= 20;
	t_circle ring = CIRCLE(pos, 3);
	t_line visdir = LINE(pos.x, pos.y, pos.x + dir.x, pos.y + dir.y);
	// printf("\nring\n");
	ft_draw_ring(p, &ring, 0xFF0000);
	// printf("\nline\n");
	ft_draw_line(p, visdir.start, visdir.end, 0xFFCC00);
}

void draw_view(t_program *p)
{
	static double	angle = (90.0 / WIN_WIDTH) * DEG_TO_RAD;
	static double	half = (90.0 / 2.0 * DEG_TO_RAD);
	t_xy			wall;
	double			column;

	printf("plr dir %f %f\n", p->plr.dir.x, p->plr.dir.y);
	column = 0;
	while (column < WIN_WIDTH)
	{
		t_xy angled;

		// angled = vec2_rot(p->plr.dir, column * angle - half);
		angled = p->plr.dir;
		wall = find_wall(p, p->plr.pos, angled);

		// if (column < 100 + WIN_WIDTH / 2.0)
		// 	printf("col %.0f | angle %f, col angle %f | vec2 x%f y%f   \twall x%f y%f\n", column, angle, column * angle, angled.x, angled.y, wall.x, wall.y);

		double magnitude = sqrt(wall.x * wall.x + wall.y * wall.y);
		magnitude = ft_clamp(magnitude, 0, 10);
		magnitude = ft_map(magnitude, RANGE(0, 10), RANGE(0, 1));

		if (fmod(column, 5))
			ft_draw_wall(p, column, 1 - magnitude, 0xABCDEF);
		else
			ft_draw_wall(p, column, 1 - magnitude, 0x0);

		t_xy vp = vec2_mul(p->plr.pos, 10);
		t_xy vd = vec2_mul(vec2_add(p->plr.pos, wall), 10);
		t_line line = LINE(vp.x, vp.y, vd.x, vd.y);
		ft_draw_line(p, line.start, line.end, 0xF088FF88);
		// printf("start %f %f | end %f %f\n", line.start.x, line.start.y, line.end.x, line.end.y);
		++column;
	}
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
		p.plr.pos = VEC2(5.5, 7.5);
		// p.plr.dir = VEC2(0.894427, 0.447214);
		// p.plr.dir = VEC2(0.910366, 0.413803);
		// p.plr.dir = VEC2(0, -1);
		// p.plr.dir = VEC2(0, 1);
		p.plr.dir = vec2_norm(VEC2(1, 0));

	}

	setup(&p, "test window");
	printf("test done\n");
	mlx_mouse_hook(p.win, &mouse_key, &p);
	mlx_hook(p.win, EVENT_MOUSE_MOVE, 0, &mouse_move, &p);
	mlx_hook(p.win, EVENT_CLOSE_WIN, 0, &window_close, &p);
	mlx_key_hook(p.win, &keyboard, &p);
	mlx_loop(p.mlx);
}
