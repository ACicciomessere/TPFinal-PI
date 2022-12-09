#include "sensorsdataCDT.h"

typedef struct years {
    int year;
    unsigned int countWeek;
    unsigned int countEnd;
    struct years * tail;
} yearList;

typedef struct sensor {
   char * name; // En caso de que el sensor no exista, o este removido, name estara en NULL
   unsigned long int count; // Cantidad total de peatones registrados por el sensor
} sensor;

typedef struct sensorsdataCDT {
    sensor * vec;
    unsigned int size; // Cantidad de memoria reservada en el heap para el vector y cantidad total de sensores
    unsigned int dim; // Cantidad de sensores activos
    yearList *first; //Ahora la lista de anios se accede desde aca
    yearList *idx; //iterador
} sensorsdataCDT;

sensorsdataADT newsensorsdataADT(){
    return calloc( 1, sizeof( sensorsdataCDT ) );
}

static int cmpPeopleAmount(const sensor * a,const sensor * b) {
      int c; 
      if((c = a->count - b->count) == 0) { // Entonces definimos por nombre del sensor
            if(a->name != NULL && b->name != NULL) {
                  return strcasecmp(a->name, b->name);
            }
            // en el caso de que ambos sean NULL entonces retorna 0 ya que da igual el orden entre ambos sensores, misma situacion en el caso de que alguno de los 2 sea NULL debido a que a la hora de obtener cualquier tipo de informacion no seran tomados en cuenta aquellos sensores cuyo nombre este en NULL
      }
      return c;
}

void orderByPeopleAmount(sensorsdataADT sensors) {
      qsort(sensors->vec, sensors->size, sizeof(sensor), cmpPeopleAmount);
}

unsigned int getSensorSize(sensorsdataADT sensors) {
      return sensors->size;
}

char * getSensorName(sensorsdataADT sensors, int i) {
      return sensors->vec[i].name;
}

size_t getPedestriansBySensor(sensorsdataADT sensor, int i) { // i >= 0
      if(sensor->vec[i].name != NULL) {
            return sensor->vec[i].count;
      }
      return 0;
}
//Iteradores
void toBegin(sensorsdataADT sensors) {
      for(int i = 0; i < sensors->size; i++) {
            sensors->idx = sensors->first;
      }
}

int hasNext(sensorsdataADT sns) {
      return sns->idx != NULL;
}

void next(sensorsdataADT sns) {
      sns->idx = sns->idx->tail;
}

// Query 3

#define DAYS_IN_YEAR 365
int isLeap(int year){//Checkea si un anio es bisiesto
    if(year%100==0)
        return(year%400==0);
    return(year%4==0);
}

long double getYearAvg(yList list) {//TODO: Creo que lo podriamos hacer long float, porque la precision del double es para muchos decimales, si mal no entendi intro info
      return (long double) (list->countWeek+list->countEnd)/DAYS_IN_YEAR+isLeap(list->year);
}
