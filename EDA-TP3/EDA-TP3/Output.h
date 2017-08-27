#ifndef OUTPUT_H
#define OUTPUT_H

#include<stdio.h>
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

#define SPACE 50.0

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

void Actualizar_display();
#endif //OUTPUT_H