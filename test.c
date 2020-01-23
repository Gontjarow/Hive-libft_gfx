#include "libft_gfx.h"

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
	t_circle circle;
	circle.pos = VEC2(250, 250);
	circle.r = 60;
	printf("draw\n");
	// ft_draw_circle(p, &circle, 0xFFFFFF);
	// ft_draw_circle2(p, &circle, 0xFFFFFF);
	// circle.r = 8;
	// ft_draw_circle2(p, &circle, 0xFFFFFF);
	// circle.r = 16;
	// ft_draw_circle2(p, &circle, 0xFFFFFF);
	// circle.r = 30;
	// ft_draw_circle2(p, &circle, 0xFFFFFF);
	ft_draw_circle_full(p, &circle, 0xFFA000);
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

	setup(&p, "test window");
	printf("test done\n");
	mlx_hook(p.win, EVENT_MOUSE_MOVE, 0, &mouse_move, &p);
	mlx_hook(p.win, EVENT_CLOSE_WIN, 0, &window_close, &p);
	mlx_loop(p.mlx);
}
