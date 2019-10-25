#pragma once

#include "Angel.h"

typedef Angel::vec4  point4;
typedef Angel::vec4  color4;


class cube{
public:

cube();

void init();
void draw();

void update();
void colorcube();
void MyQuad(int a, int b, int c, int d);

void updateAngle(float i[3]){theta[0] = i[0]; theta[1] = i[1]; theta[2] = i[2];}

GLuint get_quad_color_size(){return sizeof(quad_color);}
GLuint get_points_size(){return sizeof(points);}

private:

vec4 product(vec4 a, vec4 b){
  return vec4(a[0]*b[0], a[1]*b[1], a[2]*b[2], a[3]*b[3]);
}

const static int NumVertices = 36;
point4  vertices[8];

color4 material_ambient;
color4 material_diffuse;
color4 material_specular;
float material_shininess;
point4 light_position;
color4 light_ambient;
color4 light_diffuse;
color4 light_specular;

float theta[3];

point4 points[NumVertices];
color4 quad_color[NumVertices];
mat4 ctm;


vec4 viewer;

 int scale = 0;
 int width = 315;//315
 int length = 5;//
 int height = 135;//

// NOTE: SPECULAR LIGHTING to start!!
bool spec;
};
