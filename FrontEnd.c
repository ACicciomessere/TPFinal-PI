#include "sensorsdataCDT.h"

static void memError(void);

int main(int argCant, char * args[]) {
    if(argCant != 3 && argCant != 7) {
        fprintf( stderr, "ERROR en cantidad de datos introducidos\n" );
        exit(1);
    }

    FILE * mediciones = fopen(args[1], "r");
    FILE * sensores = fopen(args[2], "r");

    if(sensores == NULL || mediciones == NULL) {
        fprintf(stderr,"ERROR en encontrar los datos\n");
        exit(2);
    }

    sensorsdataADT sensors = newSensorsDataADT();
    if(sensors == NULL) {
        memError();
    }

    char currLine[ MAX_LEN ];
    fgets(currLine, MAX_LEN, sensores );
    while(fgets( currLine, MAX_LEN, sensores)) {
        if(addSensor(sensors, currLine))
            memError();
    }
    fclose(sensores);

    fgets(currLine, MAX_LEN, mediciones);
    while(fgets( currLine, MAX_LEN, mediciones)) {
        if(addMeasurements(sensors, currLine))
            memError();
    }
    fclose(mediciones);

    unsigned int sensorSize = getSensorSize(sensors);

    FILE * query1 = fopen("query1.csv", "wt");
    FILE * query2 = fopen("query2.csv", "wt");
    FILE * query3 = fopen("query3.csv", "wt");
    if(query1 == NULL || query2 == NULL || query3 == NULL) {
        fprintf(stderr, "ERROR: No se creo alguno de los archivos o no se lee");
        exit(3);
    }
    fputs("Sensor;Pedestrians\n", query1);
    fputs("Year;Weekdays_Count;Weekends_Count;Total_Count\n", query2);
    fputs("Year;Pedestrians_Avg\n", query3);

    char sAux[MAX_DIG];
    char sAux2[MAX_DIG];
    char sAux3[MAX_DIG];
    char sAux4[MAX_DIG];

    //Query 1
    orderByPeopleAmount(sensors);
    htmlTable htmlQ1 = newTable("query1.html", 2, "Sensor", "Pedestrians");
    for(int i = 0; i < sensorSize; i++) {
        char * name = getSensorName(sensors, i);
        if(name != NULL) {
            unsigned long int totalPedestrians = getPedestriansBySensor(sensors, i);
            fprintf( query1, "%s;%lu\n", name, totalPedestrians );
            itoaAux(totalPedestrians, sAux);
            addHTMLRow(htmlQ1, name, sAux );
        }
    }
    closeHTMLTable(htmlQ1);

    //Query 2
    toBegin(sensors);
    htmlTable htmlQ2 = newTable("query2.html", 4, "Year", "Weekdays_Count", "Weekends_Count", "Total_Count");
    int year;
    unsigned long int weekCount, endCount, totalCount;
    while(hasNext(sensors)){
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
    while(hasNext(sensors)){
        year = getYear(sensors);
        yearAvg = getYearAvg(sensors);
        fprintf( query3, "%i;%.2Lf\n", year, yearAvg);
        itoaAux(year, sAux);
        sprintf(sAux2,"%.2Lf",yearAvg);
        addHTMLRow(htmlQ3, sAux, sAux2 );
        next(sensors);
    }
    closeHTMLTable(htmlQ3);

    freeAll(sensors);
    fclose(query1);
    fclose(query2);
    fclose(query3);

    return 0;
}

static void memError(void){
    fprintf(stderr,"ERROR: Falta de memoria");
    exit(4);
}
