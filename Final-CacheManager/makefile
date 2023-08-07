# ejecutar desde la terminal escribiendo "make" 
# genera automáticamente el ejecutable del programa

# Wall de FLAGS si el compilador no te deja compilar
# despues ponelos devuelta para poder ver todos los warnings
# -Wall 
FLAGS = -Wall -std=c++11

programa: main.o cache.h
	$(CXX) -o $@ $^ $(FLAGS)

main.o: main.cpp cache.h
	$(CXX) -c $< $(FLAGS)

clean:
	rm *.o
	rm programa

.PHONY : clean