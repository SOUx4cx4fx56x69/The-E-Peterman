COMPILER=g++
NOTHOMEFLAGS=-I./ForCompiler/include -L./ForCompiler/lib/
FLAGS= -O2 -static-libstdc++ -static-libgcc -g3 -ggdb 
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
EXITNAME=Check
DIR=source

all:	CompileNotLinked
	$(COMPILER) obj/*.o -o bin/$(EXITNAME) $(FLAGS) $(LIBS)
CompileNotLinked:
	$(COMPILER) -c $(DIR)/menu.cpp $(FLAGS) $(LIBS) -o obj/menu.o 
	$(COMPILER) -c $(DIR)/Util.cpp $(FLAGS) $(LIBS) -o obj/Util.o
	$(COMPILER) -c $(DIR)/main.cpp $(FLAGS) $(LIBS) -o obj/main.o
CompileNotLinkedNotHome:
	$(COMPILER) -c $(DIR)/menu.cpp $(FLAGS) $(NOTHOMEFLAGS) $(LIBS) -o obj/menu.o 
	$(COMPILER) -c $(DIR)/Util.cpp $(FLAGS) $(NOTHOMEFLAGS) $(LIBS) -o obj/Util.o
	$(COMPILER) -c $(DIR)/main.cpp $(FLAGS) $(NOTHOMEFLAGS) $(LIBS) -o obj/main.o
Main-Not-Home:	CompileNotLinkedNotHome
	$(COMPILER) obj/*.o -o bin/$(EXITNAME) $(FLAGS) $(LIBS)
clean:
	rm obj/*.o
	rm bin/$(EXITNAME)
