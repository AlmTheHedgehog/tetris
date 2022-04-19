all: lab3

lab2: lab3.o primlib.o structs.o controller.o graphics.o 
	gcc -fsanitize=undefined -g $^ -o $@  -lSDL2_gfx `sdl2-config --libs` -lm

.c.o: 
	gcc -fsanitize=undefined -g -Wall -pedantic `sdl2-config --cflags` -c  $<

primlib.o: primlib.c primlib.h

testlib.o: lab2.c primlib.h

struct.o: structs.c structs.h

controller.o: controller.c controller.h

graphics.o: graphics.c graphics.h

clean:
	-rm primlib.o structs.o controller.o graphics.o lab3.o lab3

remake:
	make clean
	make