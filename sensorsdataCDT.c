#include "sensorsdataCDT.h"

typedef struct Q2 { 
    int year;
    unsigned int countWeek;
    unsigned int countEnd;
    struct Q2 * tail;
} Q2;

typedef struct sensor {
   char * name; // En caso de que el sensor no exista, o este removido, name estara en NULL
   unsigned long int countTotal; // Cantidad total de peatones registrados por el sensor
   Q2 * last; // Iterador
   Q2 * first; // Puntero al primer elemento de una lista que contiene los datos divididos por anio 
} sensor;

typedef struct sensorsdataCDT { 
    sensor * vec;
    size_t size; // Cantidad de memoria reservada en el heap para el vector
    unsigned int dim; // Cantidad de sensores
} sensorsdataCDT;

sensorsdataADT newSensorsADT(){
    return calloc( 1, sizeof( sensordataCDT ) );
}

static int cmpPeopleAmount(sensor * a, sensor * b) {
      int c;
      if((c = a->countTotal - b->countTotal) == 0) { // Entonces definimos por nombre del sensor
            if(a->name != NULL && b->name != NULL) {
                  return strcasemp(a->name, b->name);
            }
            // en el caso de que ambos sean NULL entonces retorna 0 ya que da igual el orden entre ambos sensores, misma situacion en el caso de que alguno de los 2 sea NULL debido a que a la hora de obtener cualquier tipo de informacion no seran tomados en cuenta aquellos sensores cuyo nombre este en NULL
      }
      return c;
}

void orderByPeopleAmount(sensorsdataADT sensors) {
      qsort(sensors->vec, sensors->size, sizeof(sensor), cmpPeopleAmount);
}

int getSensorSize(sensorsdataADT sensors) {
      return sensors->size;
}

char * getSensorName(sensorsADT sensors, int i) {
      return sensor->vec[i].name;
}

size_t getPedestriansBySensor(sensorsdataADT sensor, int i) { // i >= 0
      if(sensor->vec[i].name != NULL) {
            return sensor->vec[i].countTotal;
      }
      return 0;
}

// Query 2

int getMaxYear(sensorsADT sensors) {
      return sensors->maxYear;
}

void toBegin(sensorsADT sensors) {
      for(int i = 0; i < sensors->size; i++) {
            sensors->vec[i].last = sensors->vec[i].first;
      }
}

int hasNext(sensor sns) {
      return sns.last != NULL;
}

void next(sensor sns) {
      sns.last = sns.last->tail;
}

unsigned long int getTotalDaysCount(sensorsdataADT sensors, int year,unsigned long int*weekEnd, unsigned long int*week) {
      unsigned long int ans = 0;
      for(int i = 0; i < sensors->size; i++) {
            if(sensors->vec[i].name != NULL && sensors->vec[i].last->year == year) {
                  *week += sensors->vec[i].last->countWeek;
                  *weekEnd += sensors->vec[i].last->countEnd;
                  next(sensor->vec[i]);
            }
      }
      return *weekEnd+*week;
}

// Query 3

#define DIAS_ANIO 365

unsigned long double getTotalDaysProm(sensorsADT sensors, int i, int year) {
      return getTotalDaysCount(sensors, i, year) / DIAS_ANIO; //Revisar el tema de anio bisiesto
}
