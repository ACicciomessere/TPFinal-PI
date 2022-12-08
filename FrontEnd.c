#include "sensorsdataCDT.c"

int main( int argCant, char * args[] ) {
      if( argCant != 3 || argCant != 7 ){
            frpintf( stderr, 'ERROR en cantidad de datos introducidos' );
            exit(1);
      }
      FILE * sensores = fopen( args[1], "r" );
      FILE * mediciones = fopen( args[2], "r" );
      if( sensores == NULL || mediociones == NULL ){
            fprintf( stderr, 'ERROR en encontrar los datos' );
            exit(2);
      }
      sensorsADT sensors = newSensorsADT();

      int sensorSize = getSensorSize(sensors);
      
      //Query 1
      orderByPeopleAmount(sensors);

      for(int i = 0; i < sensorSize; i++) {
            char * name = getSensorName(sensors, i);
            if(name != NULL) {
                  fprintf(...);
            }
      }

      //Query 2
      int year = getMaxYear(sensors);
      toBegin(sensors);
      //el print va a tener: el anio, va a tener dias de semana, dias de fin de semana, y total
      for(int i = 0; !hasNext(sensors); next(sensors, i), i++) {
            unsigned long int weekDaysCount = getWeekDaysCount(sensors, year);
            unsigned long int weekendsDaysCount = getWeekendsDaysCount(sensors, year);
            unsigned long int total = getTotalDaysCount(sensors, )          
            fprintf(...);

            year -= 1;
      }

      return 0;
}
