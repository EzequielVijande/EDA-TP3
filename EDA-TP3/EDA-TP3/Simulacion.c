#include "Structures.h"
#include<math.h>
robot_t * createRobot(unsigned int count, unsigned int heigth, unsigned int width);
//Crea robots y los inicializa aleatoreamente. Asume que ya se ha inicializado la semilla srand(time(NULL))

void moveRobot(robot_t * robots, unsigned int heigth, unsigned int width);
//Mueve al robot. Ultiliza math.h. Asume que ya se ha inicializado la semilla srand(time(NULL))
//VERIFICAR EL CASO DE SALIRSE DEL PISO FUNCIONE CORRECTAMENTE

pos_t getRobot(robot_t * robot);
//Devuelve las coordenadas del robot

void destroyRobots(robot_t * robot);
//Destruye los robots creados

piso_t * createFloor(unsigned int heigth, unsigned int width);
//REVISAR FOR!

bool getPisoState(piso_t * piso, unsigned int fila, unsigned int columna);
//Devuelve el estado del piso
//REVISAR QUE ESTE BIEN LA CUENTA

//FALTARIA:
// sim_t * createSim (unsigned int robotCount, unsigned int heigth, unsigned int width);
// void destroySim (sim_t * sim);

robot_t * createRobot(unsigned int count, unsigned int height, unsigned int width)
{
	robot_t * robots = NULL;
	robots = malloc(sizeof(robot_t)*count);
		if (robots != NULL)
		{
			for (unsigned int i = 0; i < count; i++)
			{
				robots[i].pos.x = (width / ((double)(rand() + 1)) / 2);
				robots[i].pos.y = (height / ((double)(rand() + 1)) / 2);
				robots[i].angle = (360.0 / ((double)(rand() + 1)) / 2);
			}
		}
	return robots;
}

void moveRobot(robot_t * robots, unsigned int heigth, unsigned int width)
{
	robot_t newCoord;

	double posX = robots->pos.x;
	double posY = robots->pos.y;
	double alpha = robots->angle;

	posX = posX + cos(alpha);				//falta multiplicar al cos y al sin por la unidad
	posY = posY - sin(alpha);

	while ((posX < 0) && (posX > width) && (posY < 0) && (posY > heigth))
	{
		posX = posX - cos(alpha);				//falta multiplicar al cos y al sin por la unidad
		posY = posY - sin(alpha);

		alpha = (360.0 / ((double)(rand() + 1)) / 2);

		posX = posX - cos(alpha);				//falta multiplicar al cos y al sin por la unidad
		posY = posY - sin(alpha);
	}

	robots->pos.x = posX;
	robots->pos.y = posY;
	robots->angle = alpha;
}

pos_t getRobot(robot_t * robot)
{
	pos_t pos = { (robot->pos.x), (robot->pos.y) };

	return pos;
}

void destroyRobots(robot_t * robot)
{
	free(robot);
}

piso_t * createFloor(unsigned int height, unsigned int width)
{
	piso_t * piso = NULL;
	piso->heigth = height;
	piso->width = width;

	int cantBaldosas = (int)height*width;

	piso = malloc(sizeof(piso_t)*cantBaldosas);

	if (piso != NULL)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				(piso)->state = false;						//REVISAR!!!!!
				(piso->ubicacion).x = j*UNIT + (UNIT / 2.0);
				(piso->ubicacion).x = i*UNIT + (UNIT / 2.0);
			}
		
			
		}

		return piso;
	}
	else
	{
		free(piso);
		return piso;
	}
}

bool getPisoState(piso_t * piso, unsigned int fila, unsigned int columna)
{
	return (((piso_t *)(fila*(piso->width) + columna))->state);					//REVISAR!!!!!
}