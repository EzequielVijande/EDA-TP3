#ifndef SIMULATION_H
#define SIMULATION_H
#include "Structures.h"

robot_t* CreateRobots(unsigned int Number, unsigned int height, unsigned width, unsigned int unit);
//Crea un heap con el numero de robots a crear y les da un valor incial aleatorio
//de posicision y de angulo a cada uno. Asume que ya se ha inicializado la semilla srand(time(NULL))

void MoveRobot(robot_t *robot, unsigned int height, unsigned int width);
//Funcion que mueve un robot una unidad en la direccion correspondiente.
//Mueve al robot. Ultiliza math.h. Asume que ya se ha inicializado la semilla srand(time(NULL))
//VERIFICAR EL CASO DE SALIRSE DEL PISO FUNCIONE CORRECTAMENTE

pos_t GetRobotPos(const robot_t *robot);
//Devuelve las coordenadas de un robot determinado.

double GetRobotDir(const robot_t *robot);
//Devuelve el angulo en el que esta dirrecionado el robot.

void DestroyRobots(robot_t *robots);
//Libera la memoria usada por los robots.

piso_t* CreateFloor(unsigned int width, unsigned int height, unsigned int unit);
//Crea la memoria para el piso e inicializa todas las baldosas
//como sucias.

sim_t* CreateSim(unsigned int RobotCount, unsigned int height, unsigned int width, unsigned int unit);
//Crea y guarda todos los datos necesarios para correr la simulacion.

unsigned long RunSim2(sim_t* simulation);
//Corre la simulacion hasta limpiar todas las baldosas y devuelve
//el numero de ticks que tardo en finalizar.

void DestroyFloor(piso_t*);
//Libera la memoria del piso.

void DestroySim(sim_t* simulation);
//Lbera la memoria creada por la simulacion.

bool getPisoState(piso_t * piso, unsigned int fila, unsigned int columna);
//Devuelve el estado del piso
//REVISAR QUE ESTE BIEN LA CUENTA

pos_t getPisoLocation(piso_t * piso, unsigned int fila, unsigned int columna);
//Devuelve las coordenadas de un determinado piso.


#endif // !SIMULATION_H

