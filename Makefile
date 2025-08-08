all: libmygl2d.a game

libmygl2d.a: mygl2d.c include/mygl2d.h
	gcc -c mygl2d.c -o mygl2d.o -I include
	ar rcs libmygl2d.a mygl2d.o

game: main.c mouse.c include/mouse.h
	gcc main.c mouse.c -o game -I include -L lib -lm -lmygl2d -lglfw -lGL -lGLU -lX11 -lXrandr -lminiaudio

clean:
	rm *.o
	rm game
	rm libmygl2d.a

