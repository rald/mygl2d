#include "glfw.h"
#include "mygl2d.h"

#include <stdbool.h>

#define GAME_TITLE "mygl2d"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define clamp(val,min,max) ((val)<(min)?(min):((val)>(max)?(max):(val)))

bool quit=false;

bool isDrawing=false;

typedef struct Mouse Mouse;
struct Mouse {
	int x,y;
	bool isButtonLeftDown;
	bool isButtonRightDown;
};

Mouse mouse;

typedef struct Player Player;
struct Player {
	float x,y;
	float h,hi;
	float s;
};

Player player;

const float v[]={
  0, 0,
 -1, 1,
  2, 0,
 -1,-1,
  0, 0,
};

float t[10];
int u[10];

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

	glfwGetMousePos(&mouse.x,&mouse.y);

	if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS) {
		mouse.isButtonLeftDown=true;
	} else {
		mouse.isButtonLeftDown=false;
	}

	if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS) {
		mouse.isButtonRightDown=true;
	} else {
		mouse.isButtonRightDown=false;
	}

	if(glfwGetKey(GLFW_KEY_LEFT)==GLFW_PRESS) player.h-=player.hi;
	if(glfwGetKey(GLFW_KEY_RIGHT)==GLFW_PRESS) player.h+=player.hi;

	player.h=clampRadians(player.h);

	player.x=clamp(player.x,16,SCREEN_WIDTH-16);
	player.y=clamp(player.y,16,SCREEN_HEIGHT-16);

	if(glfwGetKey(GLFW_KEY_UP)==GLFW_PRESS) {
		float nx=player.s*cos(player.h)+player.x;
		float ny=player.s*sin(player.h)+player.y;
		player.x=nx;
		player.y=ny;
	}
}

void draw() {

  glLoadIdentity();
  glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);

	clearScreen();

	for(int i=0;i<10;i+=2) {
		t[i+0]=v[i+0]*8+player.x;
		t[i+1]=v[i+1]*8+player.y;
		rotatePoint(player.x,player.y,player.h,&t[i+0],&t[i+1]);
	}

	int u[10];
	for(int i=0;i<10;i+=2) {
		u[i+0]=(int)t[i+0];
		u[i+1]=(int)t[i+1];
	}

	drawPolygon(u,5);

  glFlush();

	glfwSwapBuffers();
}

int main(int argc, char** argv) {
  glfwInit();

	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);
  glfwOpenWindow(SCREEN_WIDTH,SCREEN_HEIGHT,0, 0, 0, 0, 0, 0,GLFW_WINDOW);
  glfwSetWindowTitle(GAME_TITLE);

	player.x=SCREEN_WIDTH/2;
	player.y=SCREEN_HEIGHT/2;
	player.h=270*M_PI/180;
	player.hi=10*M_PI/180;
	player.s=3;

	while(!quit) {
		update();
    draw();

		quit = glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);
	}
}
