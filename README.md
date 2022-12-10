Para generar el ejecutable, se debe acceder a la carpeta con los archivos fuente desde la terminal y ejecutar el comando "make all".
Alternativamente, puede utilizar el comando "Make debug" para generarlo con los flags fsanitize=address y wall, al igual que el flag g para tener toda la información sobre los errores que tiren estos. 

Para borrar el ejecutable se debe utilizar el comando "make clean".

El nombre del ejecutable sera "pedestrians".

Para correr el programa, se debe ejecutar en la terminal (una vez ya haya sido creado), con los dos argumentos correspondientes, siendo estos archivos .csv:

-Primeramente un path al archivo que contiene los datos de las mediciones con el siguiente formato:

      Year;Month;Mdate;Day;Sensor_ID;Time;Hourly_Counts

-Y finalmente un path al archivo que contiene los datos de los sensores con el siguiente formato:

      Sensor_ID;Name;Status

Luego cada Query va a dar lugar a dos tipos de salida una en archivo .csv y la segunda en archivo .html


