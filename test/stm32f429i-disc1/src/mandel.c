/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2011 Stephen Caudle <scaudle@doceme.com>
 * Copyright (C) 2012 Daniel Serpell <daniel.serpell@gmail.com>
 * Copyright (C) 2015 Piotr Esden-Tempski <piotr@esden.net>
 * Copyright (C) 2015 Chuck McManis <cmcmanis@mcmanis.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <ctype.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/systick.h>
#include <stm32f429i-disc1.h>

/* utility functions */

void mandel(float, float, float);

/* Maximum number of iterations for the escape-time calculation */
#define max_iter 32
uint16_t lcd_colors[] = {
	0x0,
	0x1f00,
	0x00f8,
	0xe007,
	0xff07,
	0x1ff8,
	0xe0ff,
	0xffff,
	0xc339,
	0x1f00 >> 1,
	0x00f8 >> 1,
	0xe007 >> 1,
	0xff07 >> 1,
	0x1ff8 >> 1,
	0xe0ff >> 1,
	0xffff >> 1,
	0xc339 >> 1,
	0x1f00 << 1,
	0x00f8 << 1,
	0x6007 << 1,
	0x6f07 << 1,
	0x1ff8 << 1,
	0x60ff << 1,
	0x6fff << 1,
	0x4339 << 1,
	0x1f00 ^ 0x6ac9,
	0x00f8 ^ 0x6ac9,
	0xe007 ^ 0x6ac9,
	0xff07 ^ 0x6ac9,
	0x1ff8 ^ 0x6ac9,
	0xe0ff ^ 0x6ac9,
	0xffff ^ 0x6ac9,
	0xc339 ^ 0x6ac9,
	0,
	0,
	0,
	0,
	0};

static int iterate(float, float);
/* Main mandelbrot calculation */
static int iterate(float px, float py)
{
	int it = 0;
	float x = 0, y = 0;
	while (it < max_iter)
	{
		float nx = x * x;
		float ny = y * y;
		if ((nx + ny) > 4)
		{
			return it;
		}
		/* Zn+1 = Zn^2 + P */
		y = 2 * x * y + py;
		x = nx - ny + px;
		it++;
	}
	return 0;
}

void mandel(float cx, float cy, float scale)
{
	int x, y;
	int change = 0;
	for (x = -120; x < 120; x++)
	{
		for (y = -160; y < 160; y++)
		{
			int i = iterate(cx + x * scale, cy + y * scale);
			if (i >= max_iter)
			{
				i = max_iter;
			}
			else
			{
				change++;
			}
			lcd_draw_pixel(x + 120, y + 160, lcd_colors[i]);
		}
	}
}

int main(void)
{
	int gen = 0;
	float scale = 0.25f, center_x = -0.5f, center_y = 0.0f;

	system_board_setup();

	/* Clock setup */
	system_clock_enable();
	system_usart_init();

	/* Enable the SDRAM attached to the board */
	sdram_init();
	/* Enable the LCD attached to the board */
	lcd_init();

	printf("System initialized.\n");

	while (1)
	{
		system_led1_toggle();
		mandel(center_x, center_y, scale);
		lcd_show_frame();				  
		/* Change scale and center */
		center_x += 0.1815f * scale;
		center_y += 0.505f * scale;
		scale *= 0.875f;
		gen++;
		if (gen > 99)
		{
			scale = 0.25f;
			center_x = -0.5f;
			center_y = 0.0f;
			gen = 0;
		}
		/*
		printf("Generation: %d\n", generation);
		printf("Cx, Cy = %9.2f, %9.2f, scale = %9.2f\n",
				center_x, center_y, scale);
		*/
	}

	return 0;
}
