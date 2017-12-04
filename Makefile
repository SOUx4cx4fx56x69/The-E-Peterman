COMPILER=g++
NOTHOMEFLAGS=-I./ForCompiler/include -L./ForCompiler/lib/ -m32
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
	$(COMPILER) -c $(DIR)/Game.cpp $(FLAGS) $(LIBS) -o obj/Game.o
CompileNotLinkedNotHome:
	$(COMPILER) -c $(DIR)/menu.cpp $(FLAGS) $(NOTHOMEFLAGS) $(LIBS) -o obj/menu.o 
	$(COMPILER) -c $(DIR)/Util.cpp $(FLAGS) $(NOTHOMEFLAGS) $(LIBS) -o obj/Util.o
	$(COMPILER) -c $(DIR)/main.cpp $(FLAGS) $(NOTHOMEFLAGS) $(LIBS) -o obj/main.o
	$(COMPILER) -c $(DIR)/Game.cpp $(FLAGS) $(LIBS) $(NOTHOMEFLAGS) -o obj/Game.o
Main-Not-Home:	CompileNotLinkedNotHome
	$(COMPILER) obj/menu.o obj/Util.o obj/main.o obj/Game.o -o bin/$(EXITNAME) $(FLAGS) $(LIBS) $(NOTHOMEFLAGS)
clean:
	rm obj/*.o
	rm bin/$(EXITNAME)
