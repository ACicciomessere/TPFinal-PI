Para generar el ejecutable, se debe acceder a la carpeta con los archivos fuente desde la terminal y ejecutar el comando "make all".

Alternativamente, puede utilizar el comando "Make debug" para generarlo con los flags fsanitize=address y wall, al igual que el flag g para tener toda la información sobre los errores que tiren estos. 

Contamos con multiples comandos "clean".

      clean: Para eliminar el ejecutable y los archivos de salida .o
      cleanhtml: Para eliminar los archivos html luego de la ejecucion
      cleancsv: Similar a cleanhtml pero para eliminar los csv
      cleanAll: Elimina todos los archivos que no son codigo fuente

El nombre del ejecutable sera "pedestrians".

Para correr el programa, se debe ejecutar en la terminal (una vez ya haya sido creado), con los dos argumentos correspondientes. 
Estos son paths para archivos .csv donde el primero contiene los datos de las mediciones y el segundo los datos de las mediciones.

-Las mediciones tendrán que estar formato

      Year;Month;Mdate;Day;Sensor_ID;Time;Hourly_Counts

-Los sensores se recibirán en este formato:

      Sensor_ID;Name;Status

Luego cada Query se encontraran 3 archivos csv nuevos con copias en html. Referirse a los clean para como eliminar lo no deseado.
