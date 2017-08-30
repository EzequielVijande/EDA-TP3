#ifndef OUTPUT_H
#define OUTPUT_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>
#include<stdlib.h>
#include<stdio.h>
#include "Structures.h"
#include "Simulation.h"
#define SPACE 80.0


//IMAGENES

#define BALDOSA_SUCIA "../Imagenes/dirtytile.png"
#define BALDOSA_LIMPIA "../Imagenes/limpio2.png"
#define ROBOT "../Imagenes/robot.png"



typedef struct
{
	ALLEGRO_BITMAP* b_limpia;
	ALLEGRO_BITMAP* b_sucia;
	ALLEGRO_BITMAP* robot;
}imagenes_t;

void ActualizarDisplay(sim_t* Simulacion, imagenes_t* imagenes);
//Recibe los datos de la simulacion y las imagenes correspondientes para actualizar el display.
//Asume que las imagenes ya estan cargadas en el tamano adecuado.
//
//NOTA: no llama a al_flip_display en ningun momento.


int PrintHistogram(unsigned int n_robots, ALLEGRO_DISPLAY* display, unsigned long* Ticks);

//Funcion que recibe los resultados de las simulaciones corridas e
//imprime en pantalla un gafico de barras mostrando la relacion entre
//la cantidad de Ticks y la cantidad de robots.
//Recibe la cantidad de robots maxima con la que se corrio la simulacion,
//el ancho y alto del display, y un puntero a un arreglo ordenado con la
//cantidad de ticks por numero de robots.
//devuelve -1 si hubo un error y 0 si fue exitosa.

//Funcion que inicializa un arreglo de punteros en NULL.
void set_null(void  **(puntero), int largo);

imagenes_t* SetImages(void);
//Funcion que carga todas las imagenes a usar en el formato adecuado.
//devuelve un puntero a una estructura con todas las imagenes.
//Devuelve NULL en caso de error.

void DestroyImages(imagenes_t*);

unsigned long RunSim1(sim_t* simulation, imagenes_t* img);

#endif //OUTPUT_H