#include "sensorsdataCDT.h"

typedef struct Q2 { 
    int anio;
    unsigned int countWeek;
    unsigned int countWeekEnd;
    struct Q2 * tail;
} Q2;

typedef struct sensor {
   char * name;
   unsigned long int countTotal; // Cantidad total de peatones registrados por el sensor
   Q2 * first; // Puntero al primer elemento de una lista que contiene los datos divididos por anio 
} sense;

typedef struct sensorsdataCDT { 
    sense * vec;
    size_t size; // Cantidad de memoria reservada en el heap
    unsigned int dim; // Cantidad de sensores
} sensorsCDT;
