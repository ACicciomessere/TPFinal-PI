#ifndef TPFINAL_PI_SENSORSDATACDT_H
#define TPFINAL_PI_SENSORSDATACDT_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "htmlTable.h"
#define MAX_LEN 128
#define MAX_DIG 11
typedef struct sensorsdataCDT* sensorsdataADT;

void itoaAux(int n, char s[]);

/*
Crea una nueva coleccion que contendra toda la informacion de los sensores y sus correspondientes mediciones. Debe ser utilizada previo a realizar el llamado a cualquier otra funcion
*/
sensorsdataADT newSensorsDataADT(void);

// Query 1

/*
Funcion que ordena el vector de sensores en forma descendente segun la cantidad total de peatones que registro el mismo. En caso de tener la misma cantidad de peatones registrado se define por orden alfabetico entre los nombres de los sensores.
*/
void orderByPeopleAmount(sensorsdataADT sensors);

/*
Retorna la cantidad total de peatones registrados por un sensor. (i >= 0, es decir al sensor con id 1 se accede utilizando i = 0).
En el caso de que un sensor no este activo, entonces retorna 0.
*/
unsigned long int getPedestriansBySensor(sensorsdataADT sensor, int i);

/*
Retorna la cantidad de memoria reservada en el heap para almacenar los sensores en la coleccion (incluye activos y removidos).
*/
unsigned int getSensorSize(sensorsdataADT sensors);

/*
Retorna el nombre del sensor al cual corresponde el id (i). (i >= 0, es decir al sensor con id 1 se accede utilizando i = 0).
*/
char * getSensorName(sensorsdataADT sensors, int i);

//Query 2 y 3

/*
Retorna el anio en el cual se encuentra el iterador
*/
int getYear(sensorsdataADT sensors);

/*
Retorna la cantidad de peatones registrados durante dias de semana en el anio en el cual se encuentra el iterador
*/
unsigned long int getWeekCount(sensorsdataADT sensors);

/*
Retorna la cantidad de peatones registrados durante dias de fin de semana en el anio en el cual se encuentra el iterador
*/
unsigned long int getCountEnd(sensorsdataADT sensors);

/*
Retorna la cantidad total de peatones registrados en el anio en el cual se encuentra el iterador
*/
unsigned long int getTotalCount(sensorsdataADT sensors);

/*
Para inicializar el iterador al ultimo anio en el cual haya mediciones. Es necesario para que las funciones tengan la mayor eficiencia posible. Se debe utilizar previo a realizar cualquier llamado a una funcion relacionada a query 2 o query 3.
*/
void toBegin(sensorsdataADT sensors);

/*
Retorna 1 en caso de que haya un elemento siguiente al cual poder acceder con el iterador, 0 si no
*/
int hasNext(sensorsdataADT sensors);

/*
Actualiza la posicion del iterador
*/
void next(sensorsdataADT sensors);

/*
Funcion que se utiliza para agregar la informacion de un sensor a la estructura
*/
int addSensor(sensorsdataADT sensor, char * string);

/*
Funcion que se utiliza para agregar la informacion de una medida a la estructura. El dia de la semana debe estar en ingles para su correcto funcionamiento.
*/
int addMeasurements( sensorsdataADT sensor, char * string );

// Query 3
/*
Retorna la cantidad total de peatones que se registraron en el anio en el cual se encuentra parado el iterador dividido la cantidad de dias del anio. (i >= 0).
*/
long double getYearAvg(sensorsdataADT sns);

/*
Libera toda la memoria reservada en el heap previamente
*/
void freeAll(sensorsdataADT sensors);

#endif //TPFINAL_PI_SENSORSDATACDT_H
