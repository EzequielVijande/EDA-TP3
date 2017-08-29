#include "Simulation.h"
#include <math.h>


//FALTARIA:
// sim_t * createSim (unsigned int robotCount, unsigned int heigth, unsigned int width);

sim_t* CreateSim(unsigned int RobotCount, unsigned int height, unsigned int width)
{
	sim_t* Sim = malloc(sizeof(sim_t));
	if (Sim != NULL)
	{
		Sim->robots = CreateRobots(RobotCount, height, width);
		Sim->robot_count = RobotCount;
		Sim->height = height;
		Sim->width = width;
		(Sim->tick_count) = 0;
		(Sim->piso )= CreateFloor(width, height);
		if (((Sim->robots) != NULL) && ((Sim->piso) != NULL))
		{
			return Sim;
		}

	}
	return NULL;

}

robot_t* CreateRobots(unsigned int Number, unsigned int height, unsigned width)
{
	robot_t * robots = NULL;
	robots = malloc(sizeof(robot_t)*Number);
		if (robots != NULL)
		{
			for (unsigned int i = 0; i < Number; i++)
			{
				robots[i].pos.x = (width / ((double)(rand() + 1)) / 2);
				robots[i].pos.y = (height / ((double)(rand() + 1)) / 2);
				robots[i].angle = (360.0 / ((double)(rand() + 1)) / 2);
			}
		}
	return robots;
}

void MoveRobot(robot_t *robots, unsigned int height, unsigned int width)
{

	double posX = robots->pos.x;
	double posY = robots->pos.y;
	double alpha = robots->angle;

	posX = posX + (UNIT)*cos(alpha);				//falta multiplicar al cos y al sin por la unidad
	posY = posY - (UNIT)*sin(alpha);

	while ((posX < 0) && (posX > width) && (posY < 0) && (posY > height))
	{
		posX = posX - (UNIT)*cos(alpha);				//falta multiplicar al cos y al sin por la unidad
		posY = posY - (UNIT)*sin(alpha);

		alpha = (360.0 / ((double)(rand() + 1)) / 2);

		posX = posX - (UNIT)*cos(alpha);				//falta multiplicar al cos y al sin por la unidad
		posY = posY - (UNIT)*sin(alpha);
	}

	robots->pos.x = posX;
	robots->pos.y = posY;
	robots->angle = alpha;
}

pos_t GetRobotPos(const robot_t *robot)
{
	pos_t pos = { (robot->pos.x), (robot->pos.y) };

	return pos;
}

double GetRobotDir(const robot_t *robot)
{
	double direction = (robot->angle);
	return direction;
}

void DestroyRobots(robot_t* robots)
{
	free(robots);
}

void DestroyFloor(piso_t* piso)
{
	free(piso);
}

piso_t* CreateFloor(unsigned int width, unsigned int height)
{
	piso_t * piso = NULL;
	

	int cantBaldosas = (int)height*width;

	piso = malloc(sizeof(piso_t)*cantBaldosas);

	if (piso != NULL)
	{
		piso->heigth = height;
		piso->width = width;
		for (unsigned int i = 0; i < height; i++)
		{
			for (unsigned int j = 0; j < width; j++)
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
	return ((piso+fila*(piso->width) + columna)->state);					//REVISAR!!!!!
}

pos_t getPisoLocation(piso_t* piso, unsigned int fila, unsigned int columna)
{
	return (((piso_t *)(piso+fila*(piso->width) + columna))->ubicacion);
}

void DestroySim(sim_t* sim)
{
	DestroyRobots(sim->robots);
	DestroyFloor(sim->piso);
	free(sim);
}