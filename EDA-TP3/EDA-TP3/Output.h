#ifndef
#define OUTPUT_H

#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"

#define SPACE 20

void PrintHistogram(unsigned int n_robots, ALLEGRO_DISPLAY* diplay, int* Ticks);
//Funcion que recibe los resultados de las simulaciones corridas e
//imprime en pantalla un gafico de barras mostrando la relacion entre
//la cantidad de Ticks y la cantidad de robots.
//Recibe la cantidad de robots maxima con la que se corrio la simulacion,
//el ancho y alto del display, y un puntero a un arreglo ordenado con la
//cantidad de ticks por numero de robots.

#endif //OUTPUT_H