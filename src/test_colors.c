#include <stdio.h>
#include "colors.h"

int		main(void)
{
	int		red = 0x00FF0000;
	int		green = 0x0000FF00;
	int		blue = 0x000000FF;
	int		a128_red = 0x80FF0000;
	int		a128_green = 0x8000FF00;
	int		a128_blue = 0x800000FF;

	printf("%#.8X inv -> %#.8X\n", red, get_opposite(red));
	printf("%#.8X inv -> %#.8X\n", blue, get_opposite(blue));
	printf("%#.8X inv -> %#.8X\n", green, get_opposite(green));
	printf("%#.8X inv -> %#.8X\n", a128_red, get_opposite(a128_red));
	printf("%#.8X inv -> %#.8X\n", a128_green, get_opposite(a128_green));
	printf("%#.8X inv -> %#.8X\n", a128_blue, get_opposite(a128_blue));
	printf("--------------------------------------------------------\n");
	printf("%#.8X shd -> %#.8X\n", red, add_shade(0.5, red));
	printf("%#.8X shd -> %#.8X\n", blue, add_shade(0.25, blue));
	printf("%#.8X shd -> %#.8X\n", green, add_shade(0.25, green));
	printf("%#.8X shd -> %#.8X\n", a128_red, add_shade(0.25, a128_red));
	printf("%#.8X shd -> %#.8X\n", a128_green, add_shade(0.25, a128_green));
	printf("%#.8X shd -> %#.8X\n", a128_blue, add_shade(0.25, a128_blue));
	return (0);
}
