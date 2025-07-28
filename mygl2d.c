#include "mygl2d.h"

void clearScreen(void) {
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
  glClear(GL_COLOR_BUFFER_BIT);
}

void drawPoint(int x, int y) {
    glPointSize(1);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2) {
  glBegin(GL_LINES);
  glVertex2i(x1, y1);
  glVertex2i(x2, y2);
  glEnd();
}

void drawRect(int x, int y, int w, int h) {
  glBegin(GL_LINE_LOOP);
  glVertex2i(x, y);
  glVertex2i(x + w, y);
  glVertex2i(x + w, y + h);
  glVertex2i(x, y + h);
  glEnd();
}

void fillRect(int x, int y, int w, int h) {
  glBegin(GL_QUADS);
  glVertex2i(x, y);
  glVertex2i(x + w, y);
  glVertex2i(x + w, y + h);
  glVertex2i(x, y + h);
  glEnd();
}

void drawOval(int cx, int cy, int rx, int ry) {
  glBegin(GL_LINE_LOOP);
  int num_segs = 100;
  for (int i = 0; i < num_segs; ++i) {
    float theta = 2.0f * 3.1415926f * (float)(i) / (float)(num_segs);
    int x = (int)(round(cx + rx * cos(theta)));
    int y = (int)(round(cy + ry * sin(theta)));
    glVertex2i(x, y);
  }
  glEnd();
}

void fillOval(int cx, int cy, int rx, int ry) {
  glBegin(GL_TRIANGLE_FAN);
  glVertex2i(cx, cy);  // Center
  int num_segs = 100;
  for (int i = 0; i <= num_segs; ++i) {
    float theta = 2.0f * 3.1415926f * (float)(i) / (float)(num_segs);
    int x = (int)(round(cx + rx * cos(theta)));
    int y = (int)(round(cy + ry * sin(theta)));
    glVertex2i(x, y);
  }
  glEnd();
}

void drawPolygon(const int* points, int num_points) {
  if (num_points < 3) return; // Need at least 3 points to draw polygon outline
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < num_points; ++i) {
    glVertex2i(points[2*i], points[2*i + 1]);
  }
  glEnd();
}

void fillPolygon(const int* points, int num_points) {
  if (num_points < 3) return; // Need at least 3 points to fill polygon
  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i < num_points; ++i) {
    glVertex2i(points[2*i], points[2*i + 1]);
  }
  glEnd();
}
