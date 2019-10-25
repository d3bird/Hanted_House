// Modified by David M. Chelberg for style
// last-modified: Mon Nov  7 11:39:05 2016
//
// rotating cube with lighting

// Comments in this version poor, also many places have poor style
// coding.  -- DMC
// Added some more comments -- DMC

// shades computed at vertices in application

#include "Angel.h"
#include "cube.h"

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

typedef Angel::vec4  point4;
typedef Angel::vec4  color4;

// Adjust this value for your taste (to speed up, make bigger, to
// slow down rotation, make smaller
GLfloat incr =0.06;

int axis = 0;
float theta[3] = {0.0, 0.0, 0.0};

GLuint buffers[2];
GLuint loc, loc2;
GLint matrix_loc;

cube* cc;

GLuint program;

// OpenGL initialization

void init(){

  // Create a vertex array object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // set up vertex buffer object

  glGenBuffers(1, buffers);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER, cc->get_points_size() + cc->get_quad_color_size(), NULL, GL_STATIC_DRAW);

  program = InitShader("vshader.glsl", "fshader.glsl");
  glUseProgram(program);

  loc = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  loc2 = glGetAttribLocation(program, "vColor");
  glEnableVertexAttribArray(loc2);
  glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(cc->get_points_size()));
  //uncomment this for the wire frame model
  //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

  glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

extern "C" void display(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear the window
    cc->draw();

  glutSwapBuffers();
}

extern "C" void mouse(int btn, int state, int x, int y)
{
  if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
  if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
  if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void spinCube()
{
  static GLint time=glutGet(GLUT_ELAPSED_TIME);
  theta[axis] += incr*(glutGet(GLUT_ELAPSED_TIME)-time);
  cc->updateAngle(theta);
  time = glutGet(GLUT_ELAPSED_TIME);

  if(theta[axis] > 360.0) theta[axis] -= 360.0;
  glutPostRedisplay();
}

extern "C" void mykey(unsigned char key, int mousex, int mousey)
{
  if(key=='q'||key=='Q') {
    exit(0);
  } 
}

int main(int argc, char** argv)
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(900, 900);
  glutCreateWindow("object viewer");
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutIdleFunc(spinCube);
  glutKeyboardFunc(mykey);
  cc = new cube();
  glewInit();

  init();

  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return(EXIT_SUCCESS);
}
