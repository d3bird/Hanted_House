// Modified by David M. Chelberg for style
// last-modified: Mon Nov  7 11:39:05 2016
//
// rotating cube with lighting

// Comments in this version poor, also many places have poor style
// coding.  -- DMC
// Added some more comments -- DMC

// shades computed at vertices in application

#include "Angel.h"
#include "table.h"
#include "chair.h"
#include "Small_table.h"

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

bool rotate = true;
bool Dtable = true;
bool Dchair = false;
bool smallTable = false;
table* tt;
chair* cc;
Smtable* sm;
GLuint program;

int x =0;
int y =0;
int z =0;

// the information for the camer pois
GLfloat camera_angle=45.0; // Camera's angle of view in degrees
GLfloat zNear;             // Camera's near clipping plane
GLfloat zFar;              // Camera's far clipping plane
GLfloat aspect;            // Window's aspect ratio (updated in reshape)
GLfloat left;
GLfloat right;
GLfloat top;
GLfloat bottom;
// Model-view and projection matrices uniform location
GLuint  Modeltrans, Projection, Modelview; 
mat4 model_view; //the transfermations per objects based off the position of the player
// OpenGL initialization

void init() {

	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// set up vertex buffer object

	glGenBuffers(1, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, cc->get_points_size() + cc->get_quad_color_size() + cc->get_loc_size(), NULL, GL_STATIC_DRAW);

	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	loc2 = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc2);
	glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(cc->get_points_size()));

	Modelview = glGetUniformLocation(program, "model_view");
	Modeltrans = glGetUniformLocation(program, "model_trans");
  	Projection = glGetUniformLocation(program, "Projection");

	//uncomment this for the wire frame model
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

extern "C" void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear the window
	if (Dtable) {
		tt-> ShaderModelVeiw(Modeltrans);
		tt->draw();
	}
	if (Dchair) {
		cc->draw();
	}
	if (smallTable) {
		sm->draw();
	}
	glutSwapBuffers();
}

extern "C" void mouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void spinCube() {

  point4 at(0.0, 0.0, 0.0, 1.0);
  vec4   up(0.0, 1.0, 0.0, 0.0);

	static GLint time = glutGet(GLUT_ELAPSED_TIME);
	theta[axis] += incr * (glutGet(GLUT_ELAPSED_TIME) - time);
	if (rotate) {
		tt->updateAngle(theta);
		cc->updateAngle(theta);
		sm->updateAngle(theta);
	}
	time = glutGet(GLUT_ELAPSED_TIME);

	if (theta[axis] > 360.0) theta[axis] -= 360.0;

	point4 eye(0, 0.0, -1, 1.0);
  model_view = LookAt(eye, at, up);
  glUniformMatrix4fv(Modelview, 1, GL_TRUE, model_view);

	glutPostRedisplay();
}

extern "C" void mykey(unsigned char key, int mousex, int mousey) {
	switch (key)
	{
	case 'q':
	case 'Q':
		exit(0);
		break;
	case 'r':
		rotate = !rotate;
		break;
	case '+':
		cc->increaseScale();
		break;
	case '-':
		cc->decreaseScale();
		break;

	case 'a':
		cc->increase(0);
		break;
	case 's':
		cc->increase(1);
		break;
	case 'd':
		cc->increase(2);
		break;

	case 'z':
		cc->moveleg(0);
		break;
	case 'x':
		cc->moveleg(1);
		break;
	case 'c':
		cc->moveleg(2);
		break;

 case '>': {
    camera_angle += 5.0;
    if (camera_angle > 175.0) {
      camera_angle = 175.0;
    }
    mat4 projection =Ortho(left, right, bottom, top, zNear, zFar);;

    glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
    glutPostRedisplay();
  }
    break;
  case '<':{
    camera_angle -= 5.0;
    if (camera_angle < 1.0) {
      camera_angle = 1.0;
    }
    mat4 projection1 = Ortho(left, right, bottom, top, zNear, zFar);;
    glUniformMatrix4fv(Projection, 1, GL_TRUE, projection1);
    glutPostRedisplay();
  }
	case 'w':

	break;
	default:
		// glutSetWindowTitle(key);
		break;
	}
	///	mat4 projection1 = Perspective(camera_angle, aspect, zNear, zFar);
	//	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection1);
	//	glutPostRedisplay();
}

extern "C" void menustatus(int status, int x, int y) {
	axis = 2;
	glutPostRedisplay();
}

extern "C" void myMenu(int value)
{
	switch (value) {
	case 0:
		Dtable = true;
		Dchair = false;
		smallTable = false;
		break;
	case 1:
		Dchair = true;
		Dtable = false;
		smallTable = false;
		break;
	case 3:
		Dchair = false;
		Dtable = false;
		smallTable = true;
		break;
	case 4:

		break;
	case 5:

		break;
	default:
		break;
	}
	glutPostRedisplay();
}

extern "C" void reshape(int width, int height)
{
  glViewport(0, 0, width, height);

  GLfloat left = -2.0, right = 2.0;
  GLfloat top = 2.0, bottom = -2.0;

  // Use following for ortho projection
  //  GLfloat zNear = -20.0, zFar = 20.0;

  // Use following for perspective projection
  zNear = 0.2;
  zFar = 40.0;

  aspect = GLfloat(width)/height;

  if (aspect > 1.0) {
    left *= aspect;
    right *= aspect;
  }
  else {
    top /= aspect;
    bottom /= aspect;
  }

  //mat4 projection = Perspective(camera_angle, aspect, zNear, zFar);

  // Can use either perspective or ortho projection.
    mat4 projection = Ortho(left, right, bottom, top, zNear, zFar);
  glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}
// Create menu items
void setupMenu() {
	glutCreateMenu(myMenu);
	glutAddMenuEntry("draw table", 0);
	glutAddMenuEntry("draw chair", 1);
	glutAddMenuEntry("draw small table", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(900, 900);
	glutCreateWindow("object viewer");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutIdleFunc(spinCube);
	glutKeyboardFunc(mykey);
	setupMenu();
	glutMenuStatusFunc(menustatus);

	tt = new table();
	cc = new chair();
	sm = new Smtable();
	glewInit();

	init();

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return(EXIT_SUCCESS);
}
