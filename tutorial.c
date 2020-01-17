#include "libft_gfx.h"

double	clamp(double in, double min, double max)
{
	if (in < min)
		return (min);
	else if (in > max)
		return (max);
	else
		return (in);
}

int		rgb2int(double r, double g, double b)
{
	int color;

	color = 0;
	r = clamp(r, 0, 1);
	g = clamp(g, 0, 1);
	b = clamp(b, 0, 1);
	color |= (int)(r * 255) << 16;
	color |= (int)(g * 255) << 8;
	color |= (int)(b * 255);
	return (color);
}

typedef struct  s_program
{
    void *mlx;
    void *win;
}               t_program;

int draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
    double deltaX = endX - beginX;
    double deltaY = endY - beginY;
    int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
    deltaX /= pixels;
    deltaY /= pixels;
    double pixelX = beginX;
    double pixelY = beginY;
    while (pixels)
    {
        mlx_pixel_put(mlx, win, pixelX, pixelY, color);
        pixelX += deltaX;
        pixelY += deltaY;
        --pixels;
    }
}

int mouse_event(int button, int x, int y, void *param)
{
    t_program *tutorial = param;
    mlx_pixel_put(tutorial->mlx, tutorial->win, 640/2, 360/2, 0xFFFFFF);
    return (1);
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Draw Pixel");

    t_program tutorial;
    tutorial.mlx = mlx;
    tutorial.win = win;

    mlx_mouse_hook(win, &mouse_event, &tutorial);

    mlx_loop(mlx);
}
