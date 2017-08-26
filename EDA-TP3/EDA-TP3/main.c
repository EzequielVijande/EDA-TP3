#include"Output.h"
#include<allegro5\allegro.h>
#include"allegro5\allegro_color.h"
#include"allegro5\allegro_font.h"
#include"allegro5\allegro_primitives.h"
#include"allegro5\allegro_ttf.h

int main(int argc, char* argv[])
{
	ALLEGRO_DISPLAY *display = NULL;

	if (!al_init()) 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_font_addon())
	{
		fprintf(stderr, "failed to initialize font adddon!\n");
		return -1;
	}

	if (!al_init_ttf_addon())
	{
		fprintf(stderr, "failed to initialize ttf adddon!\n");
		return -1;
	}
	if (!al_init_primitives_addon)
	{
		fprintf(stderr, "failed to initialize primitives adddon!\n");
		return -1;
	}

	display = al_create_display(800, 800);
	if (display == NULL)
	{
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	unsigned int n_robots = 5;
	unsigned long Ticks[5] = {60, 43, 31, 27, 8};
	PrintHistogram(n_robots, display, Ticks);
	al_rest(10);
	al_destroy_display(display);


	return 0;
}
