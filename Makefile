COMPILER=g++
FLAGS= -O2 -static-libstdc++ -static-libgcc -g3 -ggdb
LIBS = -lSDL2 -lSDL2_image
DIR=source
Main:
	$(COMPILER) $(DIR)/menu.cpp $(DIR)/Util.cpp $(DIR)/main.cpp $(FLAGS) $(LIBS) -o bin/Check 
Clean:
	rm *.o
