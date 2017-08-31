#include"Output.h"
#include<stdio.h>
#include<stdlib.h>
#include<allegro5\allegro.h>
#include<allegro5\allegro_color.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_ttf.h>

#define ERROR -1
#define MAX_ITERATIONS 1000

int Initialization(void);
//Inicializa Allegro y sus addons.
//Devuelve -1 si hubo error, sino devuelve 0.

int main(int argc, char* argv[])
{
	ALLEGRO_DISPLAY *display = NULL;
	imagenes_t* imagenes = NULL;
	char mode = '2';
	unsigned long Tick_counter = 0;
	unsigned int width = 30;
	unsigned int height = 30;
	unsigned int n_robots = 1;
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
	
	

	
	
	
	
	if(mode=='1')
	{

		display = al_create_display(width * UNIT, height * UNIT);
		if (display == NULL)
		{
		fprintf(stderr, "failed to create display!\n");
		return ERROR;
		}
		sim_t* Sim= CreateSim(n_robots, height, width);
		if (Sim == NULL)
		{
		al_destroy_display(display);
		DestroyImages(imagenes);
		return -1;

		}
		ActualizarDisplay(Sim, imagenes);
		Tick_counter= RunSim1(Sim, imagenes);
		fprintf(stdout, "\nTicks: %ul\n", Tick_counter);
		al_destroy_display(display);
		al_rest(2);
		DestroySim(Sim);
		DestroyImages(imagenes);


		return 0;
	}


	//Caso2
	else if (mode == '2')
	{
		unsigned long Tick[100];
		sim_t* Sim = NULL;
		

		display = al_create_display(1080, 900);
		if (display == NULL)
		{
			fprintf(stderr, "failed to create display!\n");
			return ERROR;
		}
		Tick[0] = 0;
		for (int i = 0; i < MAX_ITERATIONS; i++)
		{
			Sim = CreateSim(1, height, width);
			if (Sim == NULL)
			{
				al_destroy_display(display);
				return ERROR;
			}
			//printf("\nHola%d\n", i);
			Tick[0] += RunSim2(Sim);
			//printf("\nHola%d\n", i);

			DestroySim(Sim);

		}
		Tick[0] /= MAX_ITERATIONS;
		unsigned int j = 1;
		printf("\nHola\n");
		do
		{
			Tick[j] = 0;
			Sim = CreateSim(j + 1, height, width);
			if (Sim == NULL)
			{
				al_destroy_display(display);
				return ERROR;
			}

			for (int i = 0; i < MAX_ITERATIONS; i++)
			{
				Tick[j] += RunSim2(Sim);
			}
			Tick[j] /= MAX_ITERATIONS;
			DestroySim(Sim);
			j++;
		} while (((Tick[j - 2]) - (Tick[j - 1])) > 4);

		PrintHistogram(j, display, Tick);
		al_flip_display();
		al_rest(6);
		al_destroy_display(display);


		return 0;
	}
	
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