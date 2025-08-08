#include <stdbool.h>

#include "miniaudio.h"
#include "glfw.h"

#include "mygl2d.h"
#include "mouse.h"



#define GAME_TITLE "mygl2d"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define clamp(val,min,max) ((val)<(min)?(min):((val)>(max)?(max):(val)))

bool quit=false;

ma_result result;
ma_engine engine;

Mouse *mouse=NULL;

bool hold=false;




bool inrect(int x,int y,int rx,int ry,int w,int h) {
	return x>=rx && x<=rx+w && y>=ry && y<=ry+h;
}

bool incirc(int x,int y,int cx,int cy,int cr) {
	return (cx-x)*(cx-x) + (cy-y)*(cy-y) < cr*cr;
}

void rotatePoint(float cx, float cy, float angleInRads,float *x,float *y) {
    float s = sin(angleInRads);
    float c = cos(angleInRads);

    // Translate point back to origin
    *x -= cx;
    *y -= cy;

    // Rotate point
    float xnew = *x * c - *y * s;
    float ynew = *x * s + *y * c;

    // Translate point back
    *x = xnew + cx;
    *y = ynew + cy;
}

const float TWO_PI = 2 * M_PI;
float clampRadians(float angle) {
    if (angle < -TWO_PI || angle > TWO_PI) {
        const float cycles = angle >= 0 ? floor(angle / TWO_PI) : ceil(angle / TWO_PI);
        return angle - cycles * TWO_PI;
    }
    return angle;
}

void update() {
	Mouse_Update(mouse);
}

void draw() {
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);

	clearScreen();

	if(mouse->isLeftButtonDown && incirc(mouse->x,mouse->y,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,32)) {
		fillCircle(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,32);
		if(!hold) {
			ma_engine_play_sound(&engine, "beep.mp3", NULL);
			hold=true;
		}
	} else {
		drawCircle(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,32);
		hold=false;
	}

	glFlush();
	glfwSwapBuffers();
}

int main(int argc, char** argv) {
	glfwInit();

	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);
	glfwOpenWindow(SCREEN_WIDTH,SCREEN_HEIGHT,0, 0, 0, 0, 0, 0,GLFW_WINDOW);
	glfwSetWindowTitle(GAME_TITLE);

	mouse=Mouse_New();

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        return -1;
    }

	while(!quit) {
		update();
		draw();

		quit = glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);
	}


	ma_engine_uninit(&engine);

	Mouse_Free(&mouse);

	return 0;
}
