#include"Output.h"
#include<stdio.h>
#include<stdlib.h>
#include<allegro5\allegro.h>
#include<allegro5\allegro_color.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_ttf.h>
#include "../EDA-TP3/config.h"
#include "../EDA-TP3/lib.h"

#define ERROR -1
#define MAX_ITERATIONS 1000

int Initialization(void);
//Inicializa Allegro y sus addons.
//Devuelve -1 si hubo error, sino devuelve 0.

int main(int argc, char* argv[])
{
	ALLEGRO_DISPLAY *display = NULL;
	imagenes_t* imagenes = NULL;


	CleanerParams_t params;
	CleanerParams_t *pC = &params;
	int CmdResult, CleanerResult;
	init_CleanerParams(pC);
	CmdResult = parseCmdLine(argc, argv, parseCallback, &params);


	if ((CmdResult == -1) || (CmdResult == 0)) 
	{
		printf("Invalid arguments or values! %d\n", CmdResult);
		return ERROR;
	}

	CleanerResult = check_Cleaner_mode(pC);
	if (CleanerResult == INC_DATA) 
	{
		printf("To few arguments!\n");
		return ERROR;
	}
	if (CleanerResult == OUT_OF_RANGE) 
	{
		printf("Valores fuera de rango!\n");
		return ERROR;
	}

	int mode = params.mode;
	unsigned long Tick_counter = 0;
	unsigned int width = params.width;
	unsigned int height = params.height;
	unsigned int n_robots = params.robots;
	
	srand(time(NULL));
	unsigned int unit = (UNIT) / (((double)width + (double)height) / 2.0);



	if (Initialization() == ERROR)
	{
		fprintf(stderr, "failed to initialize allegro and add ons!\n");
		return ERROR;
	}

	
	imagenes = SetImages(unit);

	if (imagenes == NULL)
	{
		fprintf(stderr, "failed to load images!\n");
		return ERROR;
	}
	
	

	
	
	
	//Modo1
	if(mode== 1)
	{

		display = al_create_display(width * unit, height * unit);
		if (display == NULL)
		{
		fprintf(stderr, "failed to create display!\n");
		return ERROR;
		}
		sim_t* Sim= CreateSim(n_robots, height, width, unit);
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
	else 
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
			Sim = CreateSim(1, height, width, unit);
			if (Sim == NULL)
			{
				al_destroy_display(display);
				return ERROR;
			}
			Tick[0] += RunSim2(Sim);

			DestroySim(Sim);

		}
		Tick[0] /= MAX_ITERATIONS;
		unsigned int j = 1;
		do
		{
			Tick[j] = 0;
			

			for (int i = 0; i < MAX_ITERATIONS; i++)
			{
				Sim = CreateSim(j + 1, height, width, unit);
				if (Sim == NULL)
				{
					al_destroy_display(display);
					return ERROR;
				}
				Tick[j] += RunSim2(Sim);
				DestroySim(Sim);
			}
			Tick[j] /= MAX_ITERATIONS;
			j++;
		} while (((Tick[j - 2]) - (Tick[j - 1])) > 0);
		
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