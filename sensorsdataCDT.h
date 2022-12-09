#ifndef TPFINAL_PI_SENSORSDATACDT_H
#define TPFINAL_PI_SENSORSDATACDT_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LEN 128
typedef struct sensorsdataCDT* sensorsdataADT;
typedef struct years*yList;

sensorsdataADT newSensorsDataADT(void);

// Query 1

/*
Funcion que ordena el vector de sensores en forma descendente segun la cantidad total de peatones que registro el mismo. En caso de tener la misma cantidad de peatones registrado se define su orden por orden alfabetico entre los nombres de los sensores.
*/
void orderByPeopleAmount(sensorsdataADT sensors);

/*
Retorna la cantidad total de peatones registrados por un sensor. (i >= 0).
En el caso de que un sensor no este activo, entonces retorna 0.
*/
size_t getPedestriansBySensor(sensorsdataADT sensor, int i);

/*
Retorna la cantidad posiciones reservadas en el heap para el vector.
*/
unsigned int getSensorSize(sensorsdataADT sensors);

/*
Retorna el nombre del sensor. (i >= 0).
*/
char * getSensorName(sensorsdataADT sensors, int i);

//Query 2 y 3
//Para que las funciones puedan realizarse de orden 1 es necesario poner un puntero al ultimo elemento de la lista que recorrimos

/*
Retorna el anio en el cual estas parado
*/
int getYear(sensorsdataADT sensors);

/*
Retorna la cantidad de peatones registrados durante dias de semana en el anio en el que estas parado
*/
unsigned long int getWeekCount(sensorsdataADT sensors);

/*
Retorna la cantidad de peatones registrados durante dias de fin de semana en el anio en el que estas parado
*/
unsigned long int getCountEnd(sensorsdataADT sensors);

/*
Retorna la cantidad total de peatones registrados en un mismo anio
*/
unsigned long int getTotalCount(sensorsdataADT sensors);

/*
Para inicializar el puntero al ultimo elemento en el cual nos paramos. Es necesario para que las funciones tengan la mayor eficiencia posible. Se debe utilizar previo a realizar cualquier llamado a una funcion relacionada a query 2 o query 3.
*/
void toBegin(sensorsdataADT sensors);

/*
Retorna 1 en caso de que se pueda actualizar la posicion del elemento, 0 si no
*/
int hasNext(sensorsdataADT sensors);

/*
Actualiza la posicion del elemento en el cual estamos parados
*/
void next(sensorsdataADT sensors);

// Query 3
/*
Retorna la cantidad total de peatones que se registraron en un anio completo dividido la cantidad de dias del anio. (i >= 0).
*/
long double getYearAvg(yList list); //double no puede ser unsigned lmao

#endif //TPFINAL_PI_SENSORSDATACDT_H
