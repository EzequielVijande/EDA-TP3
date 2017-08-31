#include "Output.h"
#define _USE_MATH_DEFINES
#include <math.h>



#define AXIS_COLOR "white"
#define BAR_COLOR "green"
#define BACKGROUND_COLOR "black"
#define FONT_COLOR "hotpink"
#define REFERENCE_COLOR "lightblue"
#define VECTOR_COLOR "red"
#define FONT_FILE "../Fonts/Starjedi.ttf"	

#define NO 1
#define YES 0

void ActualizarBaldosas(piso_t* baldosas, unsigned int height, unsigned int width, ALLEGRO_BITMAP* imagen_sucio, ALLEGRO_BITMAP* imagen_limpio);
//Funcion que recibe las baldosas, la cantidad de las mismas y las dos imagen para cada estado de la baldosa.
//Actualiza todas las baldosas en el display segun su estado.
//Las imagenes ya deben estar cargadas en su tamano respectivo.

void ActualizarRobots(robot_t* robots, unsigned int n_robots, ALLEGRO_BITMAP* imagen_robot);
//Funcion que recibe los robots, la cantidad de los mismos y la imagen
//que se utiliza para representarlos.
//Dibuja los robots en sus posiciones dentro del display.

int PrintHistogram(unsigned int n, ALLEGRO_DISPLAY* display, unsigned long* Ticks)
{
	
	ALLEGRO_FONT* font = al_load_ttf_font(FONT_FILE, (SPACE)/3.0, 0);
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
	unsigned long max_tick = Ticks[0];
	unsigned long ticks_per_space = max_tick / 10.0;

	
	double tick_number_y = 0.0;

	//imprime los numeros sobre el eje de ticks.
	for (int j=1; j<=10; j++)
	{
		tick_number_y = height - (SPACE)-j*tick_space;
		al_draw_textf(font, al_color_name(FONT_COLOR), (SPACE)/2.0, tick_number_y, ALLEGRO_ALIGN_CENTRE, "%lu", j*ticks_per_space);
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
		upper_left_corner_y = (height - (SPACE)) - ((Ticks[i])/((double)ticks_per_space))*tick_space;
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

void ActualizarBaldosas(piso_t* baldosas, unsigned int height, unsigned int width, ALLEGRO_BITMAP* imagen_sucio, ALLEGRO_BITMAP* imagen_limpio)
{
	bool state;
	pos_t cord;
	for (unsigned int i=0; i<height; i++) //actualiza todas las baldosas segun sus estados.
	{
		for (unsigned int j = 0; j < width; j++)
		{
			
			state = getPisoState(baldosas, i, j);
			cord = getPisoLocation(baldosas, i, j);
			
			if (state==true)
			{
				al_draw_bitmap(imagen_limpio, cord.x, cord.y, 0); //dibuja la baldosa limpia.
			}
			else
			{
				al_draw_bitmap(imagen_sucio, cord.x, cord.y, 0); //dibuja la baldosa sucia.
			}
		}
		
	}
}

void ActualizarRobots(robot_t* robots, unsigned int n_robots, ALLEGRO_BITMAP* imagen_robot)
{
	pos_t cord = { 0.0 , 0.0 };
	pos_t vector = { 0.0 , 0.0 };
	pos_t vector_head1 = { 0.0 , 0.0 }; //Representan los tres vertices del triangulo que forma
	pos_t vector_head2 = { 0.0 , 0.0 }; //la cabeza del vector.
	pos_t vector_head3 = { 0.0 , 0.0 };
	double angle = 0.0;

	for (unsigned int i = 0; i < n_robots; i++)
	{
		cord = GetRobotPos(robots + i);
		angle = GetRobotDir(robots + i);
		angle = RADIAN(angle);
		al_draw_bitmap(imagen_robot, cord.x, cord.y, 0); //dibuja el robot en su posicion del display

		(vector.x) = (cord.x) + (UNIT)*cos(angle);
		(vector.y) = (cord.y)  - (UNIT)*sin(angle);

		al_draw_line((cord.x) + (UNIT) / 2.0, (cord.y) + (UNIT) / 2.0, vector.x, vector.y, al_color_name(VECTOR_COLOR), 1.0);

		vector_head1.x = (vector.x) - ((UNIT)/10.0)*cos(M_PI / 4.0);
		vector_head1.y = (vector.y) - ((UNIT) / 10.0)*sin(M_PI / 4.0);

		vector_head2.x = (vector.x) +((UNIT) / 10.0)*cos(M_PI / 4.0);
		vector_head2.y = (vector.y) + ((UNIT) / 10.0)*sin(M_PI / 4.0);

		vector_head3.x = (vector.x) + ((UNIT) / 10.0)*cos(angle);
		vector_head3.y = (vector.y) - ((UNIT) / 10.0)*sin(angle);

		al_draw_filled_triangle(vector_head1.x, vector_head1.y, vector_head2.x, vector_head2.y, vector_head3.x, vector_head3.y, al_color_name(VECTOR_COLOR));
		//Dibuja el vector que indica la direccion del robot.Tiene modulo UNIT y parte del centro del robot.
	}
}

void ActualizarDisplay(sim_t* Simulacion, imagenes_t* imagenes)
{
	
	ActualizarBaldosas(Simulacion->piso, Simulacion->height, Simulacion->width, (imagenes->b_sucia), (imagenes->b_limpia));
	ActualizarRobots(Simulacion->robots, Simulacion->robot_count, (imagenes->robot));
}


void set_null(void  **(puntero), int largo)
{
	int i;
	for (i = 0; i<largo; i++)
	{
		puntero[i] = NULL;
	}

}

//Funciones de Imagenes

void destruir_imagenes(ALLEGRO_BITMAP  **imagen, int num_imagenes)
{
	int i;
	for (i = 0; i<num_imagenes; i++)
	{
		al_destroy_bitmap(imagen[i]);
	}
}

ALLEGRO_BITMAP * load_image_at_size(char* image_name, int size_x, int size_y)
{
	ALLEGRO_BITMAP * image = NULL;
	ALLEGRO_BITMAP * current_target = NULL;
	ALLEGRO_BITMAP * resized_image = NULL;

	current_target = al_get_target_bitmap(); //salva el target original para no perderlo

	image = al_load_bitmap(image_name);
	if (image == NULL)
	{
		return NULL;
	}

	resized_image = al_create_bitmap(size_x, size_y);
	if (resized_image == NULL)
	{
		al_destroy_bitmap(image);
		return NULL;


	}

	al_set_target_bitmap(resized_image);
	al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
		0, 0, size_x, size_y, 0);

	al_set_target_bitmap(current_target); //vuelve al target original
	al_destroy_bitmap(image);
	return resized_image;
}

imagenes_t* SetImages(void)
{
	imagenes_t* img = malloc(sizeof(imagenes_t));

	ALLEGRO_BITMAP* baldosa_limpia = load_image_at_size(BALDOSA_LIMPIA, UNIT, UNIT);
	ALLEGRO_BITMAP* baldosa_sucia = load_image_at_size(BALDOSA_SUCIA, UNIT, UNIT);
	ALLEGRO_BITMAP* robot = load_image_at_size(ROBOT, ROBOT_SIZE, ROBOT_SIZE);

	if( (baldosa_sucia == NULL)||(baldosa_limpia == NULL)||(robot == NULL)||(img==NULL) )
	{
		return NULL;
	}
	else
	{
		(img->b_limpia) = baldosa_limpia;
		(img->b_sucia) = baldosa_sucia;
		(img->robot) = robot;
		return img;
	}

}

void DestroyImages(imagenes_t* img)
{
	al_destroy_bitmap((img->b_limpia));
	al_destroy_bitmap((img->b_sucia));
	al_destroy_bitmap((img->robot));
	free(img);

}

unsigned long RunSim1(sim_t* simulation, imagenes_t* img)
{
	int count_iteration = 0;
	double posRobX = 0;
	double posRobY = 0;


	bool count_aux = true;
	bool finish = NO;

	for (unsigned int i = 0; i < (simulation->robot_count); i++) //Chequea si la posicion en la que empiezan todos los robots ya limpia las baldosas
	{
		posRobX = (((simulation->robots) + i)->pos).x;
		posRobY = (((simulation->robots) + i)->pos).y;
		((piso_t*)((simulation->piso) + (int)(simulation->width)*(int)((posRobY + ROBOT_SIZE / 2.0) / (UNIT)) + (int)((posRobX + ROBOT_SIZE / 2.0) / UNIT)))->state = true;
	}

	for (unsigned int k = 0; (k < (simulation->height)) && (count_aux); k++)
	{
		for (unsigned int j = 0; (j < (simulation->width)) && (count_aux); j++)
		{
			count_aux = getPisoState((simulation->piso), k, j);

		}
		if (k == ((simulation->height) - 1))
		{
			return 0;
		}
	}


	while (finish == NO)
	{
		
		
		for (unsigned int i = 0; i < (simulation->robot_count); i++)
		{
			posRobX = (((simulation->robots) + i)->pos).x;
			posRobY = (((simulation->robots) + i)->pos).y;

			
			MoveRobot((simulation->robots) + i, simulation->height, simulation->width);
			((piso_t*)((simulation->piso) + (int)(simulation->width)*(int)((posRobY + ROBOT_SIZE / 2.0) / (UNIT)) + (int)((posRobX + ROBOT_SIZE / 2.0) / UNIT)))->state = true;
			
			
			
			
			ActualizarDisplay(simulation, img);
			al_rest(0.05);
			al_flip_display();



		}

		for (unsigned int k = 0; (k < (simulation->height)) && (count_aux); k++)
		{
			for (unsigned int j = 0; (j < (simulation->width)) && (count_aux); j++)
			{
				count_aux = getPisoState((simulation->piso), k, j);
				
			}
			if (k == ((simulation->height)-1))
			{
				finish = YES;
			}
		}
		

		

		count_iteration++;
		count_aux = true;
	}

	return count_iteration;
}