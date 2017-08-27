//Modulo en el que se definen las estructuras generales usadas
//en el programa.

#ifndef DEFINITIONS_H

#define DEFINITIONS_H

#define SUCIO false
#define LIMPIO true
#define UNIT 20

#include <stdbool.h>
#include<stdlib.h>

typedef struct
{
	double x;
	double y;
}pos_t;

typedef struct
{
	pos_t pos;
	double angle;

}robot_t;

typedef struct
{
	unsigned int heigth;
	unsigned int width;
	pos_t ubicacion; //se considera la ubicacion respecto del centro de la baldosa.
	bool state;
}piso_t;


//Estructura en la que se guarda toda la informacion necesaria
//para correr la simulacion..
typedef struct 
{
	robot_t* robots;
	unsigned int robot_count;
	piso_t* piso;
	unsigned int width;
	unsigned int height;
	unsigned long tick_count;

}sim_t;

#endif // !DEFINITIONS_H
