OBJ_D = obj
DIR = source

all-home: 
	cd $(DIR) && make -f Makefile
all-not-home:
	cd $(DIR)  && make -f Makefile Main-Not-Home
clean:
	cd $(DIR) && make -f Makefile clean
clean-not-home:
	cd $(DIR) && make -f Makefile clean-not-home
