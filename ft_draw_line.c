#include "libft_gfx.h"

int					ft_draw_line(t_program *p, t_xy start, t_xy end, int color)
{
	t_xy	length;
	t_xy	ratio;
	int		pixels;
	int		index;
	t_xy	pos;

	length = VEC2(end.x - start.x, end.y - start.y);
	pixels = (length.x > length.y) ? (length.x) : (length.y);
	ratio.x = (start.y != end.y) ? (length.x / length.y) : 1;
	ratio.y = (start.x != end.x) ? (length.y / length.x) : 1;
	ratio.x = (ratio.x > ratio.y) ? 1 : (ratio.x);
	ratio.y = (ratio.y > ratio.x) ? 1 : (ratio.y);
	pos = VEC2(start.x, start.y);
	while (pixels--)
	{
		index = (pos.y + 0.5) * p->buffer.line_bytes + (pos.x + 0.5);
		printf("start %d %d bytes %d\n",
			(int)start.x, (int)start.y, p->buffer.line_bytes);
		printf("pixel index %d\n", index);
		p->buffer.data[index] = color;
		pos.x += ratio.x;
		pos.y += ratio.y;
	}
	return (TRUE);
}
