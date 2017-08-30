#include"Output.h"
#include<stdio.h>
#include<stdlib.h>
#include<allegro5\allegro.h>
#include<allegro5\allegro_color.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_ttf.h>

#define ERROR -1

int Initialization(void);
//Inicializa Allegro y sus addons.
//Devuelve -1 si hubo error, sino devuelve 0.

int main(int argc, char* argv[])
{
	ALLEGRO_DISPLAY *display = NULL;
	imagenes_t* imagenes = NULL;
	srand(time(NULL));

	if (Initialization() == ERROR)
	{
		fprintf(stderr, "failed to initialize allegro and add ons!\n");
		return ERROR;
	}

	
	imagenes = SetImages();

	if (imagenes == NULL)
	{
		fprintf(stderr, "failed to load images!\n");
		return ERROR;
	}
	display = al_create_display(15*UNIT, 15 * UNIT);
	if (display == NULL)
	{
		fprintf(stderr, "failed to create display!\n");
		return ERROR;
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
	
	sim_t* Sim= CreateSim(15, 15, 15);
	if (Sim == NULL)
	{
		al_destroy_display(display);
		DestroyImages(imagenes);
		return -1;

	}
	ActualizarDisplay(Sim, imagenes);
	/*for (int i = 0; i < 600; i++)
	{
		for (unsigned int j = 0; j < (Sim->robot_count); j++)
		{
			MoveRobot((Sim->robots)+j, (Sim->height), (Sim->width));
		}
		ActualizarDisplay(Sim, imagenes);
		al_rest(0.05);
		al_flip_display();
	}
	*/
	RunSim1(Sim, imagenes);

	al_flip_display();
	al_rest(2);
	al_destroy_display(display);
	DestroySim(Sim);
	DestroyImages(imagenes);


	return 0;
}

int Initialization(void)
{
	if (!al_init())
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return ERROR;
	}

	if (!al_init_font_addon())
	{
		fprintf(stderr, "failed to initialize font adddon!\n");
		return ERROR;
	}

	if (!al_init_ttf_addon())
	{
		fprintf(stderr, "failed to initialize ttf adddon!\n");
		return ERROR;
	}
	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "failed to initialize primitives adddon!\n");
		return ERROR;
	}
	if (!al_init_image_addon())
	{
		fprintf(stderr, "failed to initialize images adddon!\n");
		return ERROR;
	}

	return 0;
}