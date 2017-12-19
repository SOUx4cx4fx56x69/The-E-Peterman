COMPILER=g++
NOTHOMEFLAGS=-I../ForCompiler/include -L../ForCompiler/lib/ -m32
FLAGS= -O2 -static-libstdc++ -static-libgcc -g3 -ggdb 
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lglut -lGLU \
#-lpthread
EXITNAME=Check
OBJS = main.o Util.o Game.o menu.o
DIR=source

all:	CompileNotLinked
	$(COMPILER) $(OBJS) -o ../bin/$(EXITNAME) $(FLAGS) $(LIBS)


menu.o: menu.cpp menu.hpp
	$(COMPILER) -c menu.cpp $(FLAGS) $(LIBS) 

Util.o: Util.cpp Util.hpp
	$(COMPILER) -c Util.cpp $(FLAGS) $(LIBS) 

main.o: main.cpp main.hpp
	$(COMPILER) -c main.cpp $(FLAGS) $(LIBS) 

Game.o: Game.cpp Game.hpp
	$(COMPILER) -c Game.cpp $(FLAGS) $(LIBS) 


CompileNotLinked: $(OBJS)

AddFlags:
	$(FLAGS) += $(NOTHOMEFLAGS)

CompileNotLinkedNotHome: AddFlags all
	
	

Main-Not-Home:	CompileNotLinkedNotHome

clean:
	rm *.o
	rm ../bin/$(EXITNAME)
clean-not-home:
	del *.o
	del ../bin/$(EXITNAME)
