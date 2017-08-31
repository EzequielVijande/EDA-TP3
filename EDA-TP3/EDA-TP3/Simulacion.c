#include "Simulation.h"

#include<stdio.h>

#define NO 1
#define YES 0


//FALTARIA:
// unsigned long RunSim(sim_t* simulation);

sim_t* CreateSim(unsigned int RobotCount, unsigned int height, unsigned int width, unsigned int unit)
{
	sim_t* Sim = malloc(sizeof(sim_t));
	if (Sim != NULL)
	{
		Sim->robots = CreateRobots(RobotCount, height*(unit), width*(unit), unit);
		Sim->robot_count = RobotCount;
		Sim->height = height;
		Sim->width = width;
		Sim->unit = unit;
		(Sim->tick_count) = 0;
		(Sim->piso )= CreateFloor(width, height, unit);
		if (((Sim->robots) != NULL) && ((Sim->piso) != NULL))
		{
			return Sim;
		}

	}
	
	return NULL;

}

robot_t* CreateRobots(unsigned int Number, unsigned int height, unsigned width, unsigned int unit)
{
	robot_t * robots = NULL;
	robots = malloc(sizeof(robot_t)*Number);
		if (robots != NULL)
		{
			for (unsigned int i = 0; i < Number; i++)
			{
				(((robots+i)->pos).x) =  (rand()%width) ;
				(((robots + i)->pos).y) =  (rand()%height);
				((robots + i)->angle) = rand()%300 ;
				(robots + i)->unit = unit;
			}
			
		}
	return robots;
}

void MoveRobot(robot_t *robots, unsigned int input_height, unsigned int input_width)
{
	unsigned int unit = (robots->unit);
	double width = (double)input_width *(unit);
	double height = (double)input_height*(unit);
	double posX = robots->pos.x; //borde superior izquierdo del robot
	double posY = robots->pos.y;
	double endX = posX + ROBOT_SIZE(unit); //Borde inferior derecho del robot
	double endY = posY + ROBOT_SIZE(unit);

	double nposX = posX;
	double nposY = posY;
	double nendX = endX;
	double nendY = endY;


	double alpha = robots->angle;
	alpha = RADIAN(alpha);

	
	nposX = (posX + (unit)*cos(alpha));
	nposY = (posY - (unit)*sin(alpha));
	nendX = (endX + (unit)*cos(alpha));
	nendY = (endY - (unit)*sin(alpha));


	while ((nposX < 0) || (nposX > width) || (nposY < 0) || (nposY > height) || (nendX < 0) || (nendX > width) || (nendY < 0) || (nendY > height))
	{

		alpha = rand() % 360;
		alpha = RADIAN(alpha);
		nposX = (posX + (unit)*cos(alpha));
		nposY = (posY - (unit)*sin(alpha));
		nendX = (endX + (unit)*cos(alpha));
		nendY = (endY - (unit)*sin(alpha));
	}
	
	posX = (posX + (unit)*cos(alpha));
	posY = (posY - (unit)*sin(alpha));
	alpha = DEG(alpha);
	(robots->pos).x = posX;
	(robots->pos).y = posY;
	robots->angle = alpha;
}

pos_t GetRobotPos(const robot_t *robot)
{
	pos_t pos = { ((robot->pos).x), ((robot->pos).y) };

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

piso_t* CreateFloor(unsigned int width, unsigned int height, unsigned int unit)
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
				((piso + i*width + j)->state) = false;						//REVISAR!!!!!
				(((piso + i*width + j)->ubicacion).x) = j*unit;
				(((piso + i*width + j)->ubicacion).y) = i*unit;
			}
		
			
		}

		return piso;
	}
	else
	{
		return piso;
	}
}

bool getPisoState(piso_t * piso, unsigned int fila, unsigned int columna)
{
	return (((piso_t *)(piso + fila*(piso->width) + columna))->state);					//REVISAR!!!!!
}

pos_t getPisoLocation(piso_t* piso, unsigned int fila, unsigned int columna)
{
	return (((piso_t *)(piso + fila*(piso->width) + columna))->ubicacion);
}

void DestroySim(sim_t* sim)
{
	DestroyRobots(sim->robots);
	DestroyFloor(sim->piso);
	free(sim);
}

unsigned long RunSim2(sim_t* simulation)
{
	int count_iteration = 0;
	double posRobX = 0;
	double posRobY = 0;
	unsigned int unit = (simulation->unit);


	bool count_aux = true;
	bool finish = NO;

	for (unsigned int i = 0; i < (simulation->robot_count); i++) //Chequea si la posicion en la que empiezan todos los robots ya limpia las baldosas
	{
		posRobX = (((simulation->robots) + i)->pos).x;
		posRobY = (((simulation->robots) + i)->pos).y;
		((piso_t*)((simulation->piso) + (int)(simulation->width)*(int)((posRobY + ROBOT_SIZE(unit) / 2.0) / (unit)) + (int)((posRobX + ROBOT_SIZE(unit) / 2.0) / unit)))->state = true;
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
			posRobX = ((simulation->robots) + i)->pos.x;
			posRobY = ((simulation->robots) + i)->pos.y;

			
			MoveRobot((simulation->robots) + i, simulation->height, simulation->width);
			((simulation->piso) + (int)(simulation->width)*(int)((posRobY + ROBOT_SIZE(unit) / 2.0) / (unit)) + (int)((posRobX + ROBOT_SIZE(unit) / 2.0) / unit))->state = true;

			




		}

		for (unsigned int k = 0; (k < (simulation->height)) && (count_aux); k++)
		{
			for (unsigned int j = 0; (j < (simulation->width)) && (count_aux); j++)
			{
				count_aux = getPisoState((simulation->piso), k, j);

			}
			if (k == ((simulation->height) - 1))
			{
				finish = YES;
			}
		}




		count_iteration++;
		count_aux = true;
	}

	return count_iteration;
}





