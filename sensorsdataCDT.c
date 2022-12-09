#include "sensorsdataCDT.h"

typedef struct years {
    int year;
    unsigned long int countWeek;
    unsigned long int countEnd;
    struct years * tail;
} yearList;

typedef yearList * TYearList;

typedef struct sensor {
   char * name; // En caso de que el sensor no exista, o este removido, entonces name estara en NULL
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

int newSensor(sensorsdataADT sensor, unsigned int id, char * name, char status) {
      if(sensor->size < id) {
            sensor->vec = realloc(sensor->vec, sizeof(sensor->vec[0]) * id);
            for(int i = sensor->size; i < id; i++) {
                  sensor->vec[i].name = NULL;
                  sensor->vec[i].count = 0;
            }
            sensor->size = id;
      }
      sensor->vec[id - 1].name = malloc(strlen(name) + 1);
      strcpy(sensor->vec[id - 1].name, name);
      if(sensor->vec[id - 1].name == NULL) {
            return 1;
      }
      return 0;
}

int addSensor(sensorsdataADT sensor, char * string) {
      char * token;
      char fin[2] = ";";

      token = strtok(string, fin);

      int id = atoi(token);

      token = strtok(NULL, fin);
      char * name = token;

      token = strtok(NULL, fin);
      char status = token[0];

      if(status == 'A') {
            return newSensor(sensor, id, name, status);
      }

      return 0;
}

TYearList addYearRec(yearList * first, int year,char * date, int hourlyCounts, int id, sensor * vec, int * flag) {
      if(first == NULL || year > first->year) {
            TYearList * aux = malloc(sizeof(years));
            if(aux == NULL) {
                *flag = 1;
            }
            aux->year = year;
            if(date[0] != 'S') {
                  aux->countWeek = hourlyCounts;
                  aux->countEnd = 0;
            } else {
                  aux->countEnd = hourlyCounts;
                  aux->countWeek = 0;
            }
            vec[id - 1].count += hourlyCounts;
            aux->tail = first;
            return aux;
      }
      if(year == first->year) {
            if(date[0] != 'S') {
                  aux->countWeek += hourlyCounts;
            } else {
                  aux->countEnd += hourlyCounts;
            }
            vec[id - 1].count += hourlyCounts;
            return year;
      }
      first->tail = addYearRec(first->tail, year, name, hourlyCounts, id, vec);
      return first;
}

int newYear(sensorsdataADT sensor, int year, char * date, int hourlyCounts, int id) {
    int flag = 0;
    sensor->first = addYearRec(sensor->first, year, date, hourlyCounts, id, sensor->vec, &flag);
    return flag;
}

int addMeasurements( sensorsdataADT sensor, char * string ){
    char * token;
    char fin[2] = ";";
    
    token = strtok(string, fin);
    int year = atoi(token);
    
    token = strtok(NULL, fin);       //salteo el mes
    
    token = strtok(NULL, fin);       //salteo el dia del mes
    
    token = strtok(NULL, fin);
    char * date = token;
    
    token = strtok(NULL, fin);
    int id = atoi(token);
    
    token = strtok(NULL, fin);       //salteo time
    
    token = strtok(NULL, fin);
    unsigned long int Counts = atoi(token);
    
    return newYear( sensor, year, date, counts, id );
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

int getYear(sensorsdataADT sensors) {
      return sensors->idx->year;
}

unsigned long int getWeekCount(sensorsdataADT sensors) {
      return sensors->idx->countWeek;
}


unsigned long int getCountEnd(sensorsdataADT sensors) {
      return sensors->idx->countEnd;
}

unsigned long int getTotalCount(sensorsdataADT sensors) {
      return sensors->idx->countEnd + sensors->idx->countWeek;
}

//Iterador
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

static void freeRec(yearList * years) {
      if(years == NULL) {
            return;
      }
      freeRec(years->tail);
      free(years->name);
      free(years);
}

void freeAll(sensorsdataADT sensors) {
      freeRec(sensors->first);
      free(sensors->vec);
      free(sensors);
}
