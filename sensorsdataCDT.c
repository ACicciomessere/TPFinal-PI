#include "sensorsdataCDT.h"

typedef struct years {
    int year;
    unsigned long int countWeek;
    unsigned long int countEnd;
    struct years * tail;
} yearList;

typedef yearList * TYearList;

typedef struct sensor {
    char * name; // En caso de que el sensor no exista, o este removido, entonces name estara en NULL
    unsigned long int count; // Cantidad total de peatones registrados por el sensor
} sensor;

typedef struct sensorsdataCDT {
    sensor * vec;
    unsigned int size; // Cantidad de memoria reservada en el heap para el vector y cantidad total de sensores
    yearList *first; //Ahora la lista de anios se accede desde aca
    yearList *idx; //iterador
} sensorsdataCDT;

sensorsdataADT newSensorsDataADT(){   // Funcion para crear el espacio que va a ocupar inicialmente la estructura
    return calloc( 1, sizeof( sensorsdataCDT ) );
}

static void swap(char *x, char *y) {  // Funcion para cambiar la posicion de dos elementos de un string
    char t = *x; *x = *y; *y = t;  // Utilizada unicamente para la funcion reverse
}

static char* reverse(char *buffer, int i, int j){  // Funcion que invierte un string
    while (i < j) {                                // Utilizada unicamente en la funcion itoaAux
        swap(&buffer[i++], &buffer[j--]);
    }
    return buffer;
}

void itoaAux(int n, char s[]){   // Funcion para converitr un valor de tipo int a un string
    int i, sign;
    if(( sign = n ) < 0 )        // Guardo el signo del numero
        n = -n;
    i = 0;
    do{
        s[i++] = n%10 + '0';     // Ciclo que va guardando cada numero en el vector de chars hasta que llegue a 0
    }while((n /=  10) > 0);      
    if(sign < 0)                  
        s[i++] = '-';            // Luego si el valor es negativo le agrega el signo
    s[i] = '\0';
    reverse(s, 0, i-1);          // Finalmente lo invierte para que quede el numero como corresponde
}

int newSensor(sensorsdataADT sensor, unsigned int id, char * name) {   // Agrega a la estructura los datos de un nuevo sensor
    if (sensor->size < id) {                                                        // aumentando el espacio conforme se va necesitando
        sensor->vec = realloc(sensor->vec, sizeof(sensor->vec[0]) * id);        
        for (int i = sensor->size; i < id; i++) {
            sensor->vec[i].name = NULL;
            sensor->vec[i].count = 0;
        }
        sensor->size = id;
    }
    sensor->vec[id - 1].name = malloc(strlen(name) + 1);
    strcpy(sensor->vec[id - 1].name, name);
    if (sensor->vec[id - 1].name == NULL) {                                     // Verifica si nos quedamos sin memoria una vez agregamos un nuevo sensor
            return 1;
    }
    return 0;
}

int addSensor(sensorsdataADT sensor, char * string) {       // Lee el string dado y guarda la informacion correspondiente para luego guardarla en la estructura
    char * token;
    char fin[2] = ";";

    token = strtok(string, fin);                            // Guarda los datos en un token desde el inicio del string hasta el ";"

    int id = atoi(token);                                   // Guarda en una variable el valor del token

    token = strtok(NULL, fin);
    char * name = token;

    token = strtok(NULL, fin);
    char status = token[0];

    if(status == 'A') {         // Chequea que no agregue un sensor que se encuentra removido
        return newSensor(sensor, id, name);         // Llama a newSensor para agregar el sensor
    }

    return 0;
}

TYearList addYearRec(yearList * first, int year,char * date, int hourlyCounts, int id, sensor * vec, int * flag) {  // Agrega de forma recursiva los datos
    if(first == NULL || year > first->year) {                                                                       // de las mediciones
        yearList * aux = malloc(sizeof(yearList));
        if(aux == NULL) {
            *flag = 1;
        }
        aux->year = year;
        if(date[0] != 'S') {        //Si el string inicia con "S" entonces es porque es alguno de los dos dias del fin de semana ("Saturday" o "Sunday")
            aux->countWeek = hourlyCounts;
            aux->countEnd = 0;
        } else {
            aux->countEnd = hourlyCounts;
            aux->countWeek = 0;
        }
        vec[id - 1].count += hourlyCounts;
        aux->tail = first;
        return aux;
    }
    if(year == first->year) {
        if(date[0] != 'S') {
            first->countWeek += hourlyCounts;
        } else {
            first->countEnd += hourlyCounts;
        }
        vec[id - 1].count += hourlyCounts;
        return first;
    }
    first->tail = addYearRec(first->tail, year, date, hourlyCounts, id, vec, flag);
    return first;
}

int newYear(sensorsdataADT sensor, int year, char * date, int hourlyCounts, int id) {   // Agrega los datos de las mediciones a la estructura
    int flag = 0;
    if(id<=sensor->size&&sensor->vec[id-1].name!=NULL)
        sensor->first = addYearRec(sensor->first, year, date, hourlyCounts, id, sensor->vec, &flag);
    return flag;
}

int addMeasurements( sensorsdataADT sensor, char * string ){    // Lee el string y guarda los datos necesarios para luego agregarlos con otra funcion
    char * token;
    char fin[2] = ";";

    token = strtok(string, fin);
    int year = atoi(token);

    token = strtok(NULL, fin);       //salteo el mes

    token = strtok(NULL, fin);       //salteo el dia del mes

    token = strtok(NULL, fin);
    char * date = token;

    token = strtok(NULL, fin);
    int id = atoi(token);

    token = strtok(NULL, fin);       //salteo time

    token = strtok(NULL, fin);
    unsigned long int Counts = atoi(token);

    return newYear( sensor, year, date, Counts, id );
}

static int cmpPeopleAmount(const sensor * a,const sensor * b) { // Compara cual sensor tiene mayor cantidad de peatones que pasaron
    int c;
    if((c = b->count - a->count) == 0) { // Entonces definimos por nombre del sensor
        if(a->name != NULL && b->name != NULL) {
            return strcasecmp(a->name,b->name);
        }
        // en el caso de que ambos sean NULL entonces retorna 0 ya que da igual el orden entre ambos sensores, misma situacion en el caso de que alguno de los 2 sea NULL debido a que a la hora de obtener cualquier tipo de informacion no seran tomados en cuenta aquellos sensores cuyo nombre este en NULL
    }
    return c;
}

void orderByPeopleAmount(sensorsdataADT sensors) {  // Ordena con qsort los sensores de forma descendente
    qsort(sensors->vec, sensors->size, sizeof(sensor),(int (*) (const void*,const void*))cmpPeopleAmount);
}

unsigned int getSensorSize(sensorsdataADT sensors) {    // Devuelve la cantidad de sensores guardados
    return sensors->size;
}

char * getSensorName(sensorsdataADT sensors, int i) {   // Devuelve el nombre del sensor para la id dada
    return sensors->vec[i].name;
}

unsigned long int getPedestriansBySensor(sensorsdataADT sensor, int i) {    // Devuelve la cantidad de personas que pasaron por el sensor de la id correspondiente
    if(sensor->vec[i].name != NULL) {
        return sensor->vec[i].count;
    }
    return 0;
}

int getYear(sensorsdataADT sensors) {   // Devuelve el anio en el que se encuentra el iterador
    return sensors->idx->year;
}

unsigned long int getWeekCount(sensorsdataADT sensors) {    // Devuelve la cantidad de personas que pasaron en la semana
    return sensors->idx->countWeek;
}


unsigned long int getCountEnd(sensorsdataADT sensors) {     // Devuelve la cantidad de personas que pasaron el fin de semana
    return sensors->idx->countEnd;
}

unsigned long int getTotalCount(sensorsdataADT sensors) {   // Devuelve el total de personas que pasaron
    return sensors->idx->countEnd + sensors->idx->countWeek;
}

//Iterador
void toBegin(sensorsdataADT sensors) {  // Inicia el iterador en el principio de la lista
    for(int i = 0; i < sensors->size; i++) {
        sensors->idx = sensors->first;
    }
}

int hasNext(sensorsdataADT sns) {   // Devuelve 0 si el iterador no tiene un elemento que lo sigue
    return sns->idx != NULL;
}

void next(sensorsdataADT sns) { // Mueve el iterador al elemento siguiente de la lista
    sns->idx = sns->idx->tail;
}

// Query 3

#define DAYS_IN_YEAR 365
int isLeap(int year){   //Checkea si un anio es bisiesto
    if(year%100==0)
        return(year%400==0);
    return(year%4==0);
}

long double getYearAvg(sensorsdataADT sns) {    // Devuelve el promedio de personas que pasaron por anio
    return ((long double) sns->idx->countWeek+sns->idx->countEnd) / (DAYS_IN_YEAR+isLeap(sns->idx->year));
}

static void freeRec(yearList * years) {     // Libera la memoria utilizada en la lista de anios
    if(years == NULL) {
        return;
    }
    freeRec(years->tail);
    free(years);
}

void freeAll(sensorsdataADT sensors) {      // Libera la memoria utilizada en toda la estructura
    freeRec(sensors->first);
    for(int i=0;i<sensors->size;i++){
        free(sensors->vec[i].name);
    }
    free(sensors->vec);
    free(sensors);
}
