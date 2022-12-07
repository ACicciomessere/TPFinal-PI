#include "sensorsdataCDT.h"

typedef struct query1 {
  char * name;
  size_t count;
  size_t dim;
} query1;

typedef struct query2 {
  size_t countweek;
  size_t countweekend;
  int anio;
  size_t dim;
} query2;

typedef struct query3 {
  int year;
  size_t cantPeatones;
  size_t dim;
} query3;

typedef struct sensorsdataCDT {
  query1 * vecQ1;
  query2 * vecQ2;
  query3 * vecQ3;
} sensorsdataCDT;
