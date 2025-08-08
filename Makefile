all: libmygl2d.a game

libmygl2d.a: mygl2d.c mygl2d.h
	gcc -c mygl2d.c -o mygl2d.o
	ar rcs libmygl2d.a mygl2d.o

game: main.c mouse.c mouse.h
	gcc main.c mouse.c -o game -I. -L. -lm -lmygl2d -lglfw -lGL -lGLU -lX11 -lXrandr

clean:
	rm game
	rm mygl2d.o
	rm libmygl2d.a

