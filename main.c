#include "glfw.h"
#include "mygl2d.h"

#include <stdbool.h>

#define GAME_TITLE "mygl2d"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define clamp(val,min,max) ((val)<(min)?(min):((val)>(max)?(max):(val)))

bool quit=false;

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
	glfwPollEvents();
}

void draw() {
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);

	clearScreen();

	drawCircle(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,32);

	glFlush();
	glfwSwapBuffers();
}

int main(int argc, char** argv) {
	glfwInit();

	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);
	glfwOpenWindow(SCREEN_WIDTH,SCREEN_HEIGHT,0, 0, 0, 0, 0, 0,GLFW_WINDOW);
	glfwSetWindowTitle(GAME_TITLE);

	while(!quit) {
		update();
		draw();
		quit = glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);
	}
}

