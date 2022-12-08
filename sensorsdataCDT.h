#ifndef TPFINAL_PI_SENSORSDATACDT_H
#define TPFINAL_PI_SENSORSDATACDT_H

typedef struct sensorsdataCDT* sensorsdataADT;

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
Retorna la cantidad total de sensores activos.
*/
int getSensorsAmount(sensorsdataADT sensors);

/*
Retorna el nombre del sensor. (i >= 0).
*/
char * getSensorName(sensorsADT sensors, int i);

// Query 2

//Para que las funciones puedan realizarse de orden 1 es necesario poner un puntero al ultimo elemento de la lista que recorrimos

/*
Para inicializar el puntero al ultimo elemento en el cual nos paramos. Es necesario para que las funciones tengan la mayor eficiencia posible. Se debe utilizar previo a realizar cualquier llamado a una funcion relacionada a query 2 o query 3.
*/
void toBegin(sensorsADT sensors);

/*
Retorna el ultimo anio en el que se hayan realizado mediciones
*/
int getMaxYear(sensorsADT sensors);

/*
Retorna la cantidad de peatones que se registraron durante dias de semana en un mismo anio. (i >= 0).
*/
unsigned long int getWeekDaysCount(sensorsADT sensors, int i, int year);

/*
Retorna la cantidad de peatones que se registraron durante dias de fin de semana en un mismo anio. (i >= 0).
*/
unsigned long int getWeekendsDaysCount(sensorsADT sensors, int i, int year);

/*
Retorna la cantidad de peatones que se registraron en un anio completo. (i >= 0).
*/
unsigned long int getTotalDaysCount(sensorsADT sensors, int i, int year);

// Query 3

// Se reutiliza la funcion getYear del query 2

// Se reutiliza la funcion getTotalDaysCount del query 2

/*
Retorna la cantidad total de peatones que se registraron en un anio completo dividido la cantidad de dias del anio. (i >= 0).
*/
unsigned long double getTotalDaysProm(sensorsADT sensors, int i, int year);

#endif //TPFINAL_PI_SENSORSDATACDT_H
