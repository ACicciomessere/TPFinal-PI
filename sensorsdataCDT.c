#include "sensorsdataCDT.h"

typedef struct data{
  unsigned int year;
  unsigned int Mdate;
  char * day;   // hacer un enum para guardarlo como numero
  int hourly_counts;
}data;

typedef struct sensors{
  char * name;
  char status;
}sensors;

typedef struct sensorsdataCDT{
  data * vecD;
  sensors * vecS;
}sensorsdataCDT;
