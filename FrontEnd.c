int main() {
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
      unsigned long int weekDays=0;
      unsigned long int weekEnds=0;
      unsigned long int yearTotal=1;//Tentativo, va a estar la funcion adentro del fprintf como valor numerico
      //el print va a tener: el anio, va a tener dias de semana, dias de fin de semana, y total
      for(int i = 0; !hasNext(sensors); next(sensors, i), i++) {//Planteo la condicion de salida que total=0;
            yearTotal=getTotalCount(sensors,year,&weekEnds,&weekDays);
            fprintf(...);
            weekEnds=0;
            weekDays=0;
            year -= 1;
      }

      return 0;
}
