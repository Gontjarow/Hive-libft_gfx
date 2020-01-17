#include "libft_gfx.h"

static void setup(t_program *p, char *title)
{
	if (NULL == (p->mlx = mlx_init()))
		ft_die("MLX failed to initialize.");
	if (NULL == (p->win = mlx_new_window(p->mlx, SCRN_W, SCRN_H, title)))
		ft_die("MLX failed to create a new window.");
	if (NULL == (p->buffer.ptr = mlx_new_image(p->mlx, SCRN_W, SCRN_H)))
		ft_die("MLX failed to allocate image buffer.");
	p->size.x = SCRN_W;
	p->size.y = SCRN_H;
}

int main()
{
	t_program p;

	setup(&p, "test window");
	ft_draw_line(&p, VEC2(0,0), VEC2(SCRN_W / 2, SCRN_H / 2), 0xFFFFFF);
	mlx_put_image_to_window(p.mlx, p.win, p.buffer.ptr, 0, 0);
	printf("s\n");
	mlx_loop(p.mlx);
}
