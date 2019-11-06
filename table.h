#pragma once

#include "Angel.h"

typedef Angel::vec4  point4;
typedef Angel::vec4  color4;


class table {
public:

	table();

	void init();
	void draw();

	void update();
	void colorcube();
	void MyQuad(int a, int b, int c, int d);
	void MyQuad2(int a, int b, int c, int d);
	void updateAngle(float i[3]) { theta[0] = i[0]; theta[1] = i[1]; theta[2] = i[2]; }

	GLuint get_quad_color_size() { return sizeof(quad_color); }
	GLuint get_points_size() { return sizeof(points); }

	void changeScale(int i);
	void increaseScale();
	void decreaseScale();

	void print();

	void increase(int i);
	void decrease(int i);

	void calcMatrices();
	void ShaderModelVeiw(GLuint  m){ModelView =m;}
	void updateModelVeiwTop();
	void updateModelVeiwLeg();

	void updateVeiwer(vec4 i){ viewer =i;}
	void updateLightPos(point4 i){light_position = i;}
	bool isspecial(){return special;}
	void setspecial(bool i){special =i;}
	int getHeight(){return length + Tlength;}
	void setColor(color4 i){material_diffuse =i;}
		void setLoc(vec3 i);
private:

	vec4 product(vec4 a, vec4 b) {
		return vec4(a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]);
	}

	bool special;
	const static int NumVertices = 36;// was 36
	point4  vertices[8];// was 8
	point4  vertices2[8];// was 8

	color4 material_ambient;
	color4 material_diffuse;
	color4 material_specular;
	float material_shininess;
	point4 light_position;
	color4 light_ambient;
	color4 light_diffuse;
	color4 light_specular;

	

	point4 points[NumVertices];
	color4 quad_color[NumVertices];
	
float theta[3];
	point4 points2[NumVertices];
	color4 quad_color2[NumVertices];

	point4 Dpoints[NumVertices];

	point4 Dpoints2[NumVertices];

	vec4 viewer;
	GLuint  ModelView;
	int tscale;
	int width;//315
	int length;//
	int height;//

	int Twidth;
	int Tlength;//
	int Theight;//
	
	vec3 loc;
	//rotation matrix
	mat4 ctm;
	//transition matxi
	mat4 tloc;
	mat4 model_veiw_top;
	mat4 model_veiw_leg;
	//const GLfloat sscale = (1.0/1000.0);
	//const GLfloat none = 1;
	//mat4 scale = Scale(sscale, sscale, sscale, none);
	// NOTE: SPECULAR LIGHTING to start!!
	bool spec;
};
