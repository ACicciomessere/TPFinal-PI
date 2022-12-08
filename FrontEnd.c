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
      sensorsdataADT sensors = newSensorsADT();
      if( sensors == NULL ){       //chequear si hay memoria pero lo tenemos que agregar en el .c en el newSensorsADT
            ...
      }
      int sensorSize = getSensorSize(sensors);
      
      char * currLine[ MAX_LEN ];
      fgets( currLine, MAX_LEN, sensors );
      while( fgets( currLine, MAX_LEN, sensors ) ){
            if( ... )    //de nuevo una fun para saber que nos quedamos sin memoria
      }
      fclose( sensors );
      
      fgets( currLine, MAX_LEN, mediciones );
      while( fgets( currLine, MAX_LEN, mediciones ) ){
            if( ... )    //de nuevo una fun para saber que nos quedamos sin memoria
      }
      fclose( mediciones );
      
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
      unsigned long int weekDays=0;
      unsigned long int weekEnds=0;
      unsigned long int yearTotal=1;//Tentativo, va a estar la funcion adentro del fprintf como valor numerico
      //el print va a tener: el anio, va a tener dias de semana, dias de fin de semana, y total
      for(int i = 0; !hasNext(sensors); next(sensors, i), i++) {//Planteo la condicion de salida que total=0;
            yearTotal=getTotalCount(sensors,year,&weekEnds,&weekDays);
            fprintf(...);
            weekEnds=0;
            weekDays=0;
            year--;
      }

      return 0;
}
