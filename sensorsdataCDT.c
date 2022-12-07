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
}sensorsdataCDT;

sensorsdataADT newSensorsADT(){
    return calloc( 1, sizeof( sensordataCDT ) );
}

void newSensor( sensordataADT sensor, int id, char * name, int anio, int Mdate, char * date, int hourly_counts ){
    enum week{ Monday, Tuesday , Wednesday, Thursday, Friday, Saturday, Sunday };
    enum week day;
    day = date;    // hay que agarrar y agregar si el vector esta en NULL o si el año no esta en la lista. Si el año esta entonces hay que sumarle a donde corresponda
}
