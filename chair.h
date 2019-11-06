#pragma once

#include "Angel.h"

typedef Angel::vec4  point4;
typedef Angel::vec4  color4;


class chair {
public:

	chair();

	void init();
	void draw();

	void update();
	void colorcube();
	void MyQuad(int a, int b, int c, int d);
	void MyQuad2(int a, int b, int c, int d);
	void MyQuad3(int a, int b, int c, int d);
	void updateAngle(float i[3]) { theta[0] = i[0]; theta[1] = i[1]; theta[2] = i[2]; }

	GLuint get_quad_color_size() { return sizeof(quad_color); }
	GLuint get_points_size() { return sizeof(points); }
	GLuint get_loc_size() { return sizeof(loc); }

	void changeScale(int i);
	void increaseScale();
	void decreaseScale();

	void print();

	void increase(int i);
	void decrease(int i);

	void moveleg(int i);


	void calTranMat();
	void setLoc(vec3 i);

	int getHeight(){return Tlength + length;}

	void updateVeiwer(vec4 i){ viewer =i;}
	void updateLightPos(point4 i){light_position = i;}
	bool isspecial(){return special;}
	void setspecial(bool i){special =i;}

	void setColor(color4 i){material_diffuse =i;}
private:

	vec4 product(vec4 a, vec4 b) {
		return vec4(a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]);
	}

	bool special;
	const static int NumVertices = 36;// was 36
	point4  vertices[8];// was 8
	point4  vertices2[8];// was 8
	point4  vertices3[8];
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


	color4 quad_color2[NumVertices];
	point4 points2[NumVertices];// the dimentions for the leg
	point4 points3[NumVertices];// the vertices to draw the differnt legs
	point4 points4[NumVertices];
	point4 points5[NumVertices];

	//the vertices for the back of the chair

	point4 points6[NumVertices];
	point4 points7[NumVertices];



	vec3 loc;

	vec4 viewer;

	int scale;
	int width;//315
	int length;//
	int height;//

	int Twidth;
	int Tlength;//
	int Theight;//

	int Bwidth;
	int Blength;//
	int Bheight;//

	//rotation transformation 
	mat4 ctm;

	//transformation for the location in the world 
	mat4 tloc;

	mat4 model_veiw_base;
	mat4 model_veiw_leg1;
	mat4 model_veiw_leg2;
	mat4 model_veiw_leg3;
	mat4 model_veiw_leg4;
	mat4 model_veiw_back1;
	mat4 model_veiw_back2;

	//transformation for each of the leg
	mat4 BLleg;
	mat4 BRleg;

	mat4 FLleg;
	mat4 RRleg;

	mat4 back1;
	mat4 back2;
	// NOTE: SPECULAR LIGHTING to start!!
	bool spec;
};
