#include "Output.h"
#define AXIS_COLOR "white"
#define BAR_COLOR "green"
#define BACKGROUND_COLOR "black"
#define TICKS_PER_SPACE 0.1
#define FONT_COLOR "hotpink"
#define REFERENCE_COLOR "lightblue"
#define FONT_FILE "..\\Fonts\\Starjedi.ttf"	

int PrintHistogram(unsigned int n, ALLEGRO_DISPLAY* display, unsigned long* Ticks)
{
	ALLEGRO_FONT* font = al_load_ttf_font(FONT_FILE, (SPACE) / 4.0, 0);
	if (font == NULL)
	{
		return -1;
	}
	
	al_set_target_backbuffer(display);
	al_clear_to_color(al_color_name(BACKGROUND_COLOR)); //pinta el display.

	unsigned int height = al_get_display_height(display);
	unsigned int width = al_get_display_width(display);

	double plane_width = width - 2.0*SPACE;
	double plane_height = height - 2.0*SPACE;

	double tick_space = plane_height / 11.0;
	double tick_number_y = 0.0;

	//imprime los numeros sobre el eje de ticks.
	for (int j=1; j<=10; j++)
	{
		tick_number_y = height - (SPACE)-j*tick_space;
		al_draw_textf(font, al_color_name(FONT_COLOR), (SPACE)/2.0, tick_number_y, ALLEGRO_ALIGN_CENTRE, "%d", TICKS_PER_SPACE*j*SPACE);
	}
	al_draw_text(font, al_color_name(REFERENCE_COLOR), (SPACE) / 2.0, (SPACE) / 2.0, ALLEGRO_ALIGN_CENTRE, "Tick");


	double bar_width = plane_width / (double)(n + 1);
	double bar_space = bar_width / (double)(n - 1);


	al_draw_line(SPACE, height-SPACE, width-SPACE, height - SPACE, al_color_name(AXIS_COLOR), 2.0);
	//Dibuja el eje donde se representa el numero de robots

	al_draw_line(SPACE, height - SPACE, SPACE, SPACE, al_color_name(AXIS_COLOR), 2.0);
	//dibuja el eje donde se representa el numero de Ticks.

	double upper_left_corner_x = 0.0;
	double upper_left_corner_y = 0.0;
	double lower_right_corner_x = 0.0;
	double lower_right_corner_y = 0.0;

	double number_x = 0.0;

	for (unsigned int i = 0; i < n; i++)
	{
		upper_left_corner_x = (SPACE)+i*(bar_width + bar_space);
		upper_left_corner_y = (height - (SPACE)) - (Ticks[i])*(TICKS_PER_SPACE)*(SPACE);
		lower_right_corner_x = upper_left_corner_x + bar_space;
		lower_right_corner_y = height - SPACE;

		al_draw_filled_rectangle(upper_left_corner_x, upper_left_corner_y, lower_right_corner_x, lower_right_corner_y, al_color_name(BAR_COLOR));
		//Dibuja la barra correspondiente al robot

		number_x = (upper_left_corner_x+ lower_right_corner_x)/2.0;

		al_draw_textf(font, al_color_name(FONT_COLOR), number_x, height - ((SPACE) / 2.0), ALLEGRO_ALIGN_CENTRE, "%d", i+1);
		//imprime el numero de robots abajo de la barra correspondiente.
	}

	al_draw_text(font, al_color_name(REFERENCE_COLOR), width- (SPACE) / 2.0, height- (SPACE) / 2.0, ALLEGRO_ALIGN_CENTRE, "Robs");
	al_destroy_font(font);
	return 0;


}