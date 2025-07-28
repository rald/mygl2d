#ifndef GLPRIMITIVES_H
#define GLPRIMITIVES_H

#include <GL/gl.h>
#include <math.h>

void clearScreen(void);
void drawPoint(int x, int y);
void drawLine(int x1, int y1, int x2, int y2);
void drawRect(int x, int y, int w, int h);
void fillRect(int x, int y, int w, int h);
void drawOval(int cx, int cy, int rx, int ry);
void fillOval(int cx, int cy, int rx, int ry);
void drawPolygon(const int* points, int num_points);
void fillPolygon(const int* points, int num_points);

#endif // GLPRIMITIVES_H

