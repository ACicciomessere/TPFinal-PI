#include "sensorsdataCDT.h"

static void memError(void); //Imprime error de memoria, modularizado por su frecuencia posible

int main(int argCant, char * args[]) {
    if(argCant != 3 && argCant != 7) {      //Revisa que se introduzcan unicamente la cantidad de datos requeridos
        fprintf( stderr, "ERROR en cantidad de datos introducidos\n" );
        exit(1);
    }

    FILE * mediciones = fopen(args[1], "r");
    FILE * sensores = fopen(args[2], "r");

    if(sensores == NULL || mediciones == NULL) {    //Revisa que ninguno de los archivos dados este vacio
        fprintf(stderr,"ERROR en encontrar los datos\n");
        exit(2);
    }

    sensorsdataADT sensors = newSensorsDataADT();
    if(sensors == NULL) {   //Revisa que se haya podido alocar memoria a la estructura
        memError();
    }

    char currLine[ MAX_LEN ];       
    
    fgets(currLine, MAX_LEN, sensores );    // Saltea el encabezado del archivo introducido
    while(fgets( currLine, MAX_LEN, sensores)) {    // Ciclo para guardar en memoria los datos de los archivos
        if(addSensor(sensors, currLine))    // Agrega los datos. Retorna positivo si no se pudo almacenar algo
            memError();
    }
    fclose(sensores);

    fgets(currLine, MAX_LEN, mediciones);   // Idem al bloque anterior pero para las mediciones
    while(fgets( currLine, MAX_LEN, mediciones)) {
        if(addMeasurements(sensors, currLine))
            memError();
    }
    fclose(mediciones);

    unsigned int sensorSize = getSensorSize(sensors);

    FILE * query1 = fopen("query1.csv", "wt");  // Crea los archivos .csv para cada query
    FILE * query2 = fopen("query2.csv", "wt");
    FILE * query3 = fopen("query3.csv", "wt");
    if(query1 == NULL || query2 == NULL || query3 == NULL) {    // Se asegura de que se hayan creado correctamente los archivos
        fprintf(stderr, "ERROR: No se creo alguno de los archivos o es inaccesible");
        exit(3);
    }
    fputs("Sensor;Pedestrians\n", query1);  // Asigna encabezados a los archivos .csv 
    fputs("Year;Weekdays_Count;Weekends_Count;Total_Count\n", query2);
    fputs("Year;Pedestrians_Avg\n", query3);

    char sAux[MAX_DIG]; // Se crea un vector de chars para guardar los numeros en strings ya que es necesario para el .html
    char sAux2[MAX_DIG]; //Se reutilizan para no utilizar mas meoria de la necesaria
    char sAux3[MAX_DIG];
    char sAux4[MAX_DIG];

    //Query 1
    orderByPeopleAmount(sensors);   // Se ordenan los sensores en forma descendiente por cantidad de peatones registrados
    htmlTable htmlQ1 = newTable("query1.html", 2, "Sensor", "Pedestrians"); //Crea una tabla con los encabezados para el primer archivo .html
    for(int i = 0; i < sensorSize; i++) {
        char * name = getSensorName(sensors, i);
        if(name != NULL) {
            unsigned long int totalPedestrians = getPedestriansBySensor(sensors, i);
            fprintf( query1, "%s;%lu\n", name, totalPedestrians );      // Imprime linea por linea en el .csv
            itoaAux(totalPedestrians, sAux);    // Pasa el valor de total de personas a string
            addHTMLRow(htmlQ1, name, sAux );    // Agrega fila por fila los datos en el .html
        }
    }
    closeHTMLTable(htmlQ1); //Cierra el primer archivo .html
    fclose(query1); //Cierra el primer archivo .csv

    //Query 2
    toBegin(sensors);
    htmlTable htmlQ2 = newTable("query2.html", 4, "Year", "Weekdays_Count", "Weekends_Count", "Total_Count");//Crea el segundo archivo html con su encabezado
    int year;
    unsigned long int weekCount, endCount, totalCount;
    while(hasNext(sensors)){    // Ciclo que recorre los anios y obtiene los datos que se van guardando en el .csv y en el .html
        year = getYear(sensors);
        weekCount = getWeekCount(sensors);
        endCount = getCountEnd(sensors);
        totalCount = getTotalCount(sensors);
        fprintf( query2, "%i;%lu;%lu;%lu\n", year , weekCount , endCount, totalCount );//Print directo al archivo .csv
        itoaAux(year, sAux); //Parseo de datos a string
        itoaAux(weekCount, sAux2);
        itoaAux(endCount, sAux3);
        itoaAux(totalCount, sAux4);
        addHTMLRow(htmlQ2, sAux, sAux2, sAux3, sAux4 ); //Print a las columnas de la tabla del archivo .html
        next(sensors);
    }
    closeHTMLTable(htmlQ2); //Cierra el segundo archivo html
    fclose(query2); //Cierra el segundo archivo .csv

    //Query 3
    toBegin(sensors);
    long double yearAvg;
    htmlTable htmlQ3 = newTable("query3.html", 2, "Year", "Pedestrians_Avg");//Crea el tercer y ultimo archivo html
    while(hasNext(sensors)){    // Ciclo que recorre los anios y guarda en el .csv y el .html los datos de anios y su promedio de personas por anio
        year = getYear(sensors);
        yearAvg = getYearAvg(sensors);
        fprintf( query3, "%i;%.2Lf\n", year, yearAvg);//Mismo comportamiento que el query 2
        itoaAux(year, sAux);
        sprintf(sAux2,"%.2Lf",yearAvg);
        addHTMLRow(htmlQ3, sAux, sAux2 );
        next(sensors);
    }
    closeHTMLTable(htmlQ3);//Cierra el tercer y ultimo archivo html
    fclose(query3);//cierra el tercer y ultimo archivo csv
    
    freeAll(sensors);   // Libera la memoria
    
    return 0;
}

static void memError(void){    
    fprintf(stderr,"ERROR: Falta de memoria");
    exit(4);
}
