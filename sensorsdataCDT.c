#include "sensorsdataCDT.h"

typedef struct Q2 { 
    int anio;
    unsigned int countWeek;
    unsigned int countWeekEnd;
    struct Q2 * tail;
} Q2;

typedef struct sensor {
   char * name; // En caso de que el sensor no exista, o este removido, name estara en NULL
   unsigned long int countTotal; // Cantidad total de peatones registrados por el sensor
   Q2 * first; // Puntero al primer elemento de una lista que contiene los datos divididos por anio 
} sensor;

typedef struct sensorsdataCDT { 
    sensor * vec;
    size_t size; // Cantidad de memoria reservada en el heap para el vector
    unsigned int dim; // Cantidad de sensores
} sensorsdataCDT;
