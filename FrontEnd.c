#include "sensorsdataCDT.h"

static void memError(void);

int main(int argCant, char * args[]) {
    if(argCant != 3 && argCant != 7) {      // Chequea que se introduzcan unicamente la cantidad de datos requeridos
        fprintf( stderr, "ERROR en cantidad de datos introducidos\n" );
        exit(1);
    }

    FILE * mediciones = fopen(args[1], "r");
    FILE * sensores = fopen(args[2], "r");

    if(sensores == NULL || mediciones == NULL) {    // Chequea que ninguno de los archivos dados este vacio
        fprintf(stderr,"ERROR en encontrar los datos\n");
        exit(2);
    }

    sensorsdataADT sensors = newSensorsDataADT();
    if(sensors == NULL) {   // Chequea que la estructura tenga memoria inicialmente
        memError();
    }

    char currLine[ MAX_LEN ];       
    
    fgets(currLine, MAX_LEN, sensores );    // Saltea el encabezado del archivo introducido
    while(fgets( currLine, MAX_LEN, sensores)) {    // Hace un ciclo que guarda linea por linea en la estructura los datos
        if(addSensor(sensors, currLine))    // Agrega los datos y a su vez devuelve 1 si se queda sin memoria
            memError();
    }
    fclose(sensores);

    fgets(currLine, MAX_LEN, mediciones);   // Hace lo mismo que el bloque anterior pero con los datos de las mediciones
    while(fgets( currLine, MAX_LEN, mediciones)) {
        if(addMeasurements(sensors, currLine))
            memError();
    }
    fclose(mediciones);

    unsigned int sensorSize = getSensorSize(sensors);

    FILE * query1 = fopen("query1.csv", "wt");  // Crea los archivos .csv para cada query
    FILE * query2 = fopen("query2.csv", "wt");
    FILE * query3 = fopen("query3.csv", "wt");
    if(query1 == NULL || query2 == NULL || query3 == NULL) {    // Chequea que se hayan creado correctamente los archivos
        fprintf(stderr, "ERROR: No se creo alguno de los archivos o no se lee");
        exit(3);
    }
    fputs("Sensor;Pedestrians\n", query1);  // Ponen los encabezados en el .csv 
    fputs("Year;Weekdays_Count;Weekends_Count;Total_Count\n", query2);
    fputs("Year;Pedestrians_Avg\n", query3);

    char sAux[MAX_DIG]; // Se crea un vector de chars para guardar los numeros en strings ya que es necesario para el .html
    char sAux2[MAX_DIG];
    char sAux3[MAX_DIG];
    char sAux4[MAX_DIG];

    //Query 1
    orderByPeopleAmount(sensors);   // Ordena en orden descendente
    htmlTable htmlQ1 = newTable("query1.html", 2, "Sensor", "Pedestrians"); //Crea una tabla con los encabezados dados para el archivo .html
    for(int i = 0; i < sensorSize; i++) {
        char * name = getSensorName(sensors, i);
        if(name != NULL) {
            unsigned long int totalPedestrians = getPedestriansBySensor(sensors, i);
            fprintf( query1, "%s;%lu\n", name, totalPedestrians );      // Imprime linea por linea en el .csv
            itoaAux(totalPedestrians, sAux);    // Pasa el valor de total de personas a string
            addHTMLRow(htmlQ1, name, sAux );    // Agrega fila por fila los datos en el .html
        }
    }
    closeHTMLTable(htmlQ1); //Cierra la tabla del .html

    //Query 2
    toBegin(sensors);
    htmlTable htmlQ2 = newTable("query2.html", 4, "Year", "Weekdays_Count", "Weekends_Count", "Total_Count");
    int year;
    unsigned long int weekCount, endCount, totalCount;
    while(hasNext(sensors)){    // Ciclo que recorre los anios y obtiene los datos que se van guardando en el .csv y en el .html
        year = getYear(sensors);
        weekCount = getWeekCount(sensors);
        endCount = getCountEnd(sensors);
        totalCount = getTotalCount(sensors);
        fprintf( query2, "%i;%lu;%lu;%lu\n", year , weekCount , endCount, totalCount );
        itoaAux(year, sAux);
        itoaAux(weekCount, sAux2);
        itoaAux(endCount, sAux3);
        itoaAux(totalCount, sAux4);
        addHTMLRow(htmlQ2, sAux, sAux2, sAux3, sAux4 );
        next(sensors);
    }
    closeHTMLTable(htmlQ2);

    //Query 3
    toBegin(sensors);
    long double yearAvg;
    htmlTable htmlQ3 = newTable("query3.html", 2, "Year", "Pedestrians_Avg");
    while(hasNext(sensors)){    // Ciclo que recorre los anios y guarda en el .csv y el .html los datos de anios y su promedio de personas por anio
        year = getYear(sensors);
        yearAvg = getYearAvg(sensors);
        fprintf( query3, "%i;%.2Lf\n", year, yearAvg);
        itoaAux(year, sAux);
        sprintf(sAux2,"%.2Lf",yearAvg);
        addHTMLRow(htmlQ3, sAux, sAux2 );
        next(sensors);
    }
    closeHTMLTable(htmlQ3);

    freeAll(sensors);   // Libera la memoria
    fclose(query1);     // Cierran los archivos de cada query
    fclose(query2);
    fclose(query3);

    return 0;
}

static void memError(void){     // Funcion hecha para modularizar el error de falta de memoria
    fprintf(stderr,"ERROR: Falta de memoria");
    exit(4);
}
