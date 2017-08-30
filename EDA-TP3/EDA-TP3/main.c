#include"Output.h"
#include<stdio.h>
#include<stdlib.h>
#include<allegro5\allegro.h>
#include<allegro5\allegro_color.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_ttf.h>

int main(int argc, char* argv[])
{
	ALLEGRO_DISPLAY *display = NULL;
	imagenes_t* imagenes = NULL;
	srand(time(NULL));
	

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
	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "failed to initialize primitives adddon!\n");
		return -1;
	}
	if (!al_init_image_addon())
	{
		fprintf(stderr, "failed to initialize images adddon!\n");
		return -1;
	}

	imagenes = SetImages();

	if (imagenes == NULL)
	{
		fprintf(stderr, "failed to load images!\n");
		return -1;
	}
	display = al_create_display(10*UNIT, 10 * UNIT);
	if (display == NULL)
	{
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	unsigned int n_robots = 5;
	unsigned long Ticks[5] = {60, 43, 31, 27, 8};
	
	/*
	if(PrintHistogram(n_robots, display, Ticks) == -1)
	{
		fprintf(stderr, "failed to load font!\n");
		return -1;
	}

	
	*/
	
	sim_t* Sim= CreateSim(6, 10, 10);
	if (Sim == NULL)
	{
		al_destroy_display(display);
		DestroyImages(imagenes);

	}
	ActualizarDisplay(Sim, imagenes);
	for (int i = 0; i < 600; i++)
	{
		for (unsigned int j = 0; j < (Sim->robot_count); j++)
		{
			MoveRobot((Sim->robots)+j, (Sim->height)*(UNIT), (Sim->width)*(UNIT));
		}
		ActualizarDisplay(Sim, imagenes);
		al_rest(0.05);
		al_flip_display();
	}

	al_flip_display();
	al_rest(2);
	al_destroy_display(display);
	DestroySim(Sim);
	DestroyImages(imagenes);


	return 0;
}
