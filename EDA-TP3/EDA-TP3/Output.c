#include "Output.h"
#define AXIS_COLOR "white"
#define BAR_COLOR "green"
#define BACKGROUND_COLOR "black"
#define TICKS_PER_SPACE 0.1

void PrintHistogram(unsigned int n, ALLEGRO_DISPLAY* diplay, int* Ticks)
{
	al_set_target_backbuffer(display);
	al_clear_to_color(al_color_name(BACKGROUND_COLOR)); //pinta el display.

	unsigned int height = al_get_display_height(display);
	unsigned int width = al_get_display_width(display);

	unsigned int plane_width = width - 2.0*SPACE;
	unsigned int plane_height = height - 2.0*SPACE;

	unsigned double bar_width = plane_width / (double)(n + 1);
	unsigned double bar_space = bar_width / (double)(n - 1);


	al_draw_line(SPACE, height-SPACE, width-SPACE, height - SPACE, al_color_name(AXIS_COLOR), 2.0);
	//Dibuja el eje donde se representa el numero de robots

	al_draw_line(SPACE, height - SPACE, SPACE, SPACE, al_color_name(AXIS_COLOR), 2.0);
	//dibuja el eje donde se representa el numero de Ticks.

	unsigned double upper_left_corner_x = 0.0;
	unsigned double upper_left_corner_y = 0.0;
	unsigned double lower_right_corner_x = 0.0;
	unsigned double lower_right_corner_y = 0.0;

	for (int i = 0; i < n; i++)
	{
		upper_left_corner_x = (SPACE)+i*(bar_width + bar_space);
		upper_left_corner_y = (height - (SPACE)) - (Ticks[i - 1])*(TICKS_PER_SPACE)*(SPACE);
		lower_right_corner_x = upper_left_corner_x + bar_space;
		lower_right_corner_y = height - SPACE;

		al_draw_filled_rectangle(upper_left_corner_x, upper_left_corner_y, lower_right_corner_x, lower_right_corner_y, al_color_name(BAR_COLOR)));
		//Dibuja la barra correspondiente al robot
	}



}