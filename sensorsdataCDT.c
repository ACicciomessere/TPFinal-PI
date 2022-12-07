#include "sensorsdataCDT.h"

typedef struct Q2{ 
    int anio;
    unsigned int countWeek;
    unsigned int countWeekEnd;
    struct Q2*tail;
}Q2;

typedef struct sensor{
   char*name;
   unsigned long int countTotal;
   Q2*first;
}sense;

typedef struct sensorsdataCDT{ 
    sense*vec;
    size_t size;
    unsigned int dim;
}sensorsCDT;
