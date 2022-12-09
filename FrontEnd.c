#include "sensorsdataCDT.c"

int main( int argCant, char * args[] ) {
    if( argCant != 3 && argCant != 7 ){//!=3||!=7 es una tautologia. Quiciste decir &&?
        fprintf( stderr, 'ERROR en cantidad de datos introducidos' );
        exit(1);
    }
    FILE * sensores = fopen( args[1], "r" );
    FILE * mediciones = fopen( args[2], "r" );
    if( sensores == NULL || mediciones == NULL ){
        fprintf( stderr,'ERROR en encontrar los datos' );
        exit(2);
    }
    sensorsdataADT sensors = newSensorsDataADT();
    if( sensors == NULL ){
        //chequear si hay memoria pero lo tenemos que agregar en el .c en el newSensorsADT
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
    for(int i = 0; i < sensors->size; i++) {
        char * name = getSensorName(sensors, i);
        if(name != NULL) {
            fprintf(...);//TODO: name;sensors->vec[i].count
        }
    }

    //Query 2
    toBegin(sensors);
    while(sensors->idx!=NULL){ //TODO: Esto solo funciona si la toma de datos te arma la yearList en forma DESCENDIENTE
        fprintf(...);//sensors->idx->year;sensors->idx->countWeek;sensors->idx->countEnd;sensors->idx->countEnd+sensors->idx->countWeek
        sensors->idx=sensors->idx->tail;
    }

    //Query 3
    toBegin(sensors);
    while(sensors->idx!=NULL){
        fprintf(...);//sensors->idx->year;getYearAvg(sensors->idx)
        sensors->idx=sensors->idx->tail;
    }

    //Alternativamente, Query 2 y 3 al mismo tiempo
    toBegin(sensors);
    while(sensors->idx!=NULL) {
        fprintf(...);//Printeado a Query2.csv y Q2.html: sensors->idx->year;sensors->idx->countWeek;sensors->idx->countEnd;sensors->idx->countEnd+sensors->idx->countWeek
        fprintf(...);//Printeado a Query2.csv y Q2.html: sensors->idx->year;getYearAvg(sensors->idx)
        sensors->idx = sensors->idx->tail;
    }
        return 0;
}
