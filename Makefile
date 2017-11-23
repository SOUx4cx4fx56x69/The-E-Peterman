COMPILER=i686-w64-mingw32-g++
FLAGS= -O2 -static-libstdc++ -static-libgcc -Wpointer-arith
LIBS = -lbgi -lgdi32
DIR=source
Main:
	$(COMPILER) $(DIR)/menu.cpp $(DIR)/Util.cpp $(DIR)/main.cpp $(FLAGS) $(LIBS) -o bin/BeerGen.exe 
Clean:
	rm *.o
