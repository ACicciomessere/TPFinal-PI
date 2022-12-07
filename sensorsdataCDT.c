#include "sensorsdataCDT.h"

typedef struct query1{
  char * name;
  size_t count;
}query1;

typedef struct query2{
  size_t countweek;
  size_t countweekend;
  int anio;
}query2;

typedef struct query3{
  int anio;
  size_t cantPeatones;
}query3;

typedef struct sensorsdataCDT{
  query1 * vecQ1;
  query2 * vecQ2;
  query3 * vecQ3;
}sensorsdataCDT;

sensorsdataADT newSensorsDataADT(){
  return calloc( 1, sizeof( sensorsdataCDT ) );
}
