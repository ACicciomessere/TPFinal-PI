#include "sensorsdataCDT.c"
#include "htmlTable.c"
#define MAX_DIG 11
#define MAX_LEN 255

int main( int argCant, char * args[] ) {
    if( argCant != 3 && argCant != 7 ){//!=3||!=7 es una tautologia. Quiciste decir &&?
        fprintf( stderr, "ERROR en cantidad de datos introducidos\n" );
        exit(1);
    }
    
    FILE * sensores = fopen( args[1], "r" );
    FILE * mediciones = fopen( args[2], "r" );
    
    if( sensores == NULL || mediciones == NULL ){
        fprintf( stderr,"ERROR en encontrar los datos\n" );
        exit(2);
    }
    
    sensorsdataADT sensors = newSensorsDataADT();
    if( sensors == NULL ){
        //chequear si hay memoria pero lo tenemos que agregar en el .c en el newSensorsADT
    }

    char * currLine[ MAX_LEN ];    
    fgets( currLine, MAX_LEN, sensores );
    while( fgets( currLine, MAX_LEN, sensores ) ){
        if( ... )    //de nuevo una fun para saber que nos quedamos sin memoria
    }
    fclose( sensores );

    fgets( currLine, MAX_LEN, mediciones );
    while( fgets( currLine, MAX_LEN, mediciones ) ){
        if( ... )    //de nuevo una fun para saber que nos quedamos sin memoria
    }
    fclose( mediciones );
    
    unsigned int sensorSize = getSensorSize(sensors);
    
    FILE * query1 = fopen("query1.csv", "wt");
    FILE * query2 = fopen("query2.csv", "wt");
    FILE * query3 = fopen("query3.csv", "wt");
    if(query1 == NULL || query2 == NULL || query3 == NULL){
        fprintf(stderr, "ERROR: No se creo alguno de los archivos o no se lee");
        exit(3);
    }
    fputs("Sensor;Pedestrians\n", query1);
    fputs("Year;Weekdays_Count;Weekends_Count;Total_Count\n", query2);
    fputs("Year;Pedestrians_Avg\n", query3);
    
    char * sTotalPed[MAX_DIG];
    char * sTotalPed2[MAX_DIG];
    char * sTotalPed3[MAX_DIG];
    char * sTotalPed4[MAX_DIG];
    
    //Query 1
    orderByPeopleAmount(sensors);
    unsigned int sensorSize = getSensorSize(sensors);
    htmlTable htmlQ1 = newTable("query1", 2, "Sensor", "Pedestrians");
    for(int i = 0; i < sensorSize; i++) {
        char * name = getSensorName(sensors, i);
        if(name != NULL) {
            fprintf( query1, "%s;%lu\n", name, totalPedestrians );   //TODO: name;sensors->vec[i].count
            unsigned long int totalPedestrians = getPedestriansBySensor(sensors, i);
            itoa(totalPedestrians, sTotalPed, 10);
            addHTMLRow(htmlQ1, name, sTotalPed );
        }
    }
    closeHTMLTable(htmlQ1);

    //Query 2
    toBegin(sensors);
    htmlTable htmlQ2 = newTable("query2", 4, "Year", "Weekdays_Count", "Weekends_Count", "Total_Count");
    int year;
    unsigned long int weekCount, endCount, totalCount;
    while(hasNext(sensors)){   //TODO: Esto solo funciona si la toma de datos te arma la yearList en forma DESCENDIENTE
        year = getYear(sensors);
        weekCount = getWeekCount(sensors);
        endCount = getCountEnd(sensors);
        totalCount = getTotalCount(sensors);
        fprintf( query2, "%i;%lu;%lu;%lu\n", year , weekCount , endCount, totalCount );  //sensors->idx->year;sensors->idx->countWeek;sensors->idx->countEnd;sensors->idx->countEnd+sensors->idx->countWeek
        itoa(year, sTotalPed, 10);
        itoa(weekCount, sTotalPed2, 10);
        itoa(endCount, sTotalPed3, 10);
        itoa(totalCount, sTotalPed4, 10);
        addHTMLRow(htmlQ2, sTotalPed, sTotalPed2, sTotalPed3, sTotalPed4 );
        next(sensors);
    }
    closeHTMLTable(htmlQ2);

    //Query 3
    toBegin(sensors);
    long double yearAvg;
    htmlTable htmlQ1 = newTable("query3", 2, "Year", "Pedestrians_Avg");
    while(hasNext(sensors)){
        year = getYear(sensors);
        yearAvg = getYearAvg(sensors->idx);
        fprintf( query3, "%i;%lf\n", year, yearAvg) );   //sensors->idx->year;getYearAvg(sensors->idx)
        itoa(year, sTotalPed, 10);
        itoa(yearAvg, sTotalPed2, 10);
        addHTMLRow(htmlQ3, sTotalPed, sTotalPed2 );
        next(sensors);
    }
    closeHTMLTable(htmlQ3);

    // Alternativamente, Query 2 y 3 al mismo tiempo
    // toBegin(sensors);
    // while(hasNext(sensors)) {
    //    fprintf(...);//Printeado a Query2.csv y Q2.html: sensors->idx->year;sensors->idx->countWeek;sensors->idx->countEnd;sensors->idx->countEnd+sensors->idx->countWeek
    //    fprintf(...);//Printeado a Query2.csv y Q2.html: sensors->idx->year;getYearAvg(sensors->idx)
    //    next(sensors);
    // }
    
    freeAll(sensors);
    fclose(query1);
    fclose(query2);
    fclose(query3);
    
    return 0;
}
