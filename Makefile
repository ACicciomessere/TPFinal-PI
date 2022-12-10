COMPILER=gcc
OUTPUT_FILE=pedestrians
FLAGS=-pedantic -std=c99
DEBUG_COMPILER= -Wall -fsanitize=address -DDEBUG=1

QUERY=query1.csv query2.csv query3.csv query1.html query2.html query3.html

back.o: sensorsdataCDT.c
		$(COMPILER) -c sensorsdataCDT.c -o back.o
		
debug: COMPILER+=$(DEBUG_COMPILER)
debug: all

all:	back.o
		$(COMPILER) -o $(OUTPUT_FILE) FrontEnd.c htmlTable.c back.o $(FLAGS)
	
		
clean:
		rm -r $(OUTPUT_FILE)*.o 
