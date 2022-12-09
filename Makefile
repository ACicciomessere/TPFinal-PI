COMPILER=gcc
OUTPUT_FILE=pedestrians
FLAGS=-pedantic -std=c99
DEBUG_COMPILER=-g -Wall -fsanitize=address -DDEBUG=1

QUERY=query1.csv query2.csv query3.csv query1.htaml query2.html query3.html

debug: COMPILER+=$(DEBUG_COMPILER)
debug: all

all:	back.o
		$(COMPILER) -o $(OUTPUT_FILE) FrontEnd.c htmlTable.c back.o $(FLAGS)

debug: COMPILER+=$(DEBUG_COMPILER)
debug: all
		
back.o: sensorsdataCDT.c
		$(COMPILER) -c sensorsdataCDT.c
		
clean:
		rm -r $(OUTPUT_FILE)*.o
