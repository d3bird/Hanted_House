#include "Small_table.h"


typedef Angel::vec4  point4;
typedef Angel::vec4  color4;

Smtable::Smtable() {

	theta[0] = 0.0;
	theta[1] = 0.0;
	theta[2] = 0.0;

	material_ambient = color4(1.0, 0.0, 1.0, 1.0);
	material_diffuse = color4(1.0, 0.8, 0.0, 1.0);
	material_specular = color4(1.0, 0.8, 0.0, 1.0);
	material_shininess = 100.0;
	light_position = point4(0.0, 0.0, -1.0, 0.0);
	light_ambient = color4(0.2, 0.2, 0.2, 1.0);
	light_diffuse = color4(1.0, 1.0, 1.0, 1.0);
	light_specular = color4(1.0, 1.0, 1.0, 1.0);
	viewer = vec4(0.0, 0.0, -1.0, 0.0);
	spec = true;

	scale = 0;
	width = 135;//315
	length = 5;//
	height = 135;//

	Twidth = 10;//
	Tlength = 150;//
	Theight = 10;// not really the height but one of the dim of the sides

	loc.x = 0;
	loc.y = 0;
	loc.z = 0;


	// table stats
	vertices[0] = point4(-width, -(height), length, 1.0);
	vertices[1] = point4(-width, (height), length, 1.0);
	vertices[2] = point4(width, (height), length, 1.0);
	vertices[3] = point4(width, -(height), length, 1.0);
	vertices[4] = point4(-width, -(height), -length, 1.0);
	vertices[5] = point4(-width, (height), -length, 1.0);
	vertices[6] = point4(width, (height), -length, 1.0);
	vertices[7] = point4(width, -(height), -length, 1.0);

	//the leg


	vertices[8] = point4(-Twidth, -(Theight), Tlength, 1.0);
	vertices[9] = point4(-Twidth, (Theight), Tlength, 1.0);
	vertices[10] = point4(Twidth, (Theight), Tlength, 1.0);
	vertices[11] = point4(Twidth, -(Theight), Tlength, 1.0);

	vertices[12] = point4(-Twidth, -(Theight), -length, 1.0);
	vertices[13] = point4(-Twidth, (Theight), -length, 1.0);
	vertices[14] = point4(Twidth, (Theight), -length, 1.0);
	vertices[15] = point4(Twidth, -(Theight), -length, 1.0);

	//tloc =  Translate(width,height,0);// the location of the table

	BLleg = Translate(width, height, 0);
	BRleg = Translate(-width, -height, 0);

	FLleg = Translate(-width, height, 0);
	RRleg = Translate(width, -height, 0);
}

void Smtable::moveleg(int i) {

	switch (i) {
	case 0:
		loc.x += 2;
		break;
	case 1:
		loc.x -= 2;
		break;
	case 3:
		loc.z += 2;
		break;
	}
	changeScale(0);
}


void Smtable::MyQuad(int a, int b, int c, int d) {
	static int i = 0;

	// Compute normal vector.
	vec3 n1 = normalize(cross(ctm * vertices[b] - ctm * vertices[a], ctm * vertices[c] - ctm * vertices[b]));
	vec4 n = vec4(n1[0], n1[1], n1[2], 0.0);
	vec4 half = normalize(light_position + viewer);
	half.w = 0.0;
	color4 ambient_color, diffuse_color, specular_color;

	ambient_color = product(material_ambient, light_ambient);

	float dd = dot(light_position, n);
	if (dd > 0.0) {
		diffuse_color = dd * product(light_diffuse, material_diffuse);
	}
	else {
		diffuse_color = color4(0.0, 0.0, 0.0, 1.0);
	}

	dd = dot(half, n);
	if (dd > 0.0) {
		specular_color = exp(material_shininess * log(dd)) * product(light_specular, material_specular);
	}
	else {
		specular_color = vec4(0.0, 0.0, 0.0, 1.0);
	}
	// If we don't want specular color added
	if (!spec) {
		specular_color = vec4(0.0, 0.0, 0.0, 1.0);
	}

	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points[i] = ctm * vertices[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points[i] = ctm * vertices[b];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points[i] = ctm * vertices[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points[i] = ctm * vertices[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points[i] = ctm * vertices[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points[i] = ctm * vertices[d];
	i++;
	i %= 36;


}
// does the lighting for the legs
void Smtable::MyQuad2(int a, int b, int c, int d) {
	static int i = 0;
	// Compute normal vector.
	vec3 n1 = normalize(cross(ctm * vertices2[b] - ctm * vertices2[a], ctm * vertices2[c] - ctm * vertices2[b]));
	vec4 n = vec4(n1[0], n1[1], n1[2], 0.0);
	vec4 half = normalize(light_position + viewer);
	half.w = 0.0;
	color4 ambient_color, diffuse_color, specular_color;

	ambient_color = product(material_ambient, light_ambient);

	float dd = dot(light_position, n);
	if (dd > 0.0) {
		diffuse_color = dd * product(light_diffuse, material_diffuse);
	}
	else {
		diffuse_color = color4(0.0, 0.0, 0.0, 1.0);
	}

	dd = dot(half, n);
	if (dd > 0.0) {
		specular_color = exp(material_shininess * log(dd)) * product(light_specular, material_specular);
	}
	else {
		specular_color = vec4(0.0, 0.0, 0.0, 1.0);
	}
	// If we don't want specular color added
	if (!spec) {
		specular_color = vec4(0.0, 0.0, 0.0, 1.0);
	}

	quad_color2[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = ctm * BLleg * vertices2[a];
	points3[i] = ctm * BRleg * vertices2[a];
	points4[i] = ctm * FLleg * vertices2[a];
	points5[i] = ctm * RRleg * vertices2[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = ctm * BLleg * vertices2[b];
	points3[i] = ctm * BRleg * vertices2[b];
	points4[i] = ctm * FLleg * vertices2[b];
	points5[i] = ctm * RRleg * vertices2[b];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = ctm * BLleg * vertices2[c];
	points3[i] = ctm * BRleg * vertices2[c];
	points4[i] = ctm * FLleg * vertices2[c];
	points5[i] = ctm * RRleg * vertices2[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = ctm * BLleg * vertices2[a];
	points3[i] = ctm * BRleg * vertices2[a];
	points4[i] = ctm * FLleg * vertices2[a];
	points5[i] = ctm * RRleg * vertices2[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = ctm * BLleg * vertices2[c];
	points3[i] = ctm * BRleg * vertices2[c];
	points4[i] = ctm * FLleg * vertices2[c];
	points5[i] = ctm * RRleg * vertices2[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	//points2[i] = ctm*tloc*vertices2[d];
	//points3[i] = ctm*tloc*vertices2[d];
	points2[i] = ctm * BLleg * vertices2[d];
	points3[i] = ctm * BRleg * vertices2[d];
	points4[i] = ctm * FLleg * vertices2[d];
	points5[i] = ctm * RRleg * vertices2[d];
	i++;
	i %= 36;

}


void Smtable::colorcube() {
	MyQuad(1, 0, 3, 2);
	MyQuad(2, 3, 7, 6);
	MyQuad(3, 0, 4, 7);
	MyQuad(6, 5, 1, 2);
	MyQuad(4, 5, 6, 7);
	MyQuad(5, 4, 0, 1);

	//mat4 back = Translate(0,0,0);

	MyQuad2(1, 0, 3, 2);
	MyQuad2(2, 3, 7, 6);
	MyQuad2(3, 0, 4, 7);
	MyQuad2(6, 5, 1, 2);
	MyQuad2(4, 5, 6, 7);
	MyQuad2(5, 4, 0, 1);


}

void Smtable::changeScale(int i) {

	//the table
	vertices[0] = point4(-(width + scale), -(height + scale), (length + scale), 1.0);
	vertices[1] = point4(-(width + scale), (height + scale), (length + scale), 1.0);
	vertices[2] = point4((width + scale), (height + scale), (length + scale), 1.0);
	vertices[3] = point4((width + scale), -(height + scale), (length + scale), 1.0);
	vertices[4] = point4(-(width + scale), -(height + scale), -(length + scale), 1.0);
	vertices[5] = point4(-(width + scale), (height + scale), -(length + scale), 1.0);
	vertices[6] = point4((width + scale), (height + scale), -(length + scale), 1.0);
	vertices[7] = point4((width + scale), -(height + scale), -(length + scale), 1.0);

	//the base of the table
	vertices2[0] = point4(-(Twidth + scale), -(Theight + scale), (Tlength + scale), 1.0);
	vertices2[1] = point4(-(Twidth + scale), (Theight + scale), (Tlength + scale), 1.0);
	vertices2[2] = point4((Twidth + scale), (Theight + scale), (Tlength + scale), 1.0);
	vertices2[3] = point4((Twidth + scale), -(Theight + scale), (Tlength + scale), 1.0);
	vertices2[4] = point4(-(Twidth + scale), -(Theight + scale), -(Tlength + scale), 1.0);
	vertices2[5] = point4(-(Twidth + scale), (Theight + scale), -(Tlength + scale), 1.0);
	vertices2[6] = point4((Twidth + scale), (Theight + scale), -(Tlength + scale), 1.0);
	vertices2[7] = point4((Twidth + scale), -(Theight + scale), -(Tlength + scale), 1.0);
}

void Smtable::increaseScale(){changeScale(scale+=5);}
void Smtable::decreaseScale(){changeScale(scale-=5);}

void Smtable::increase(int i) {
	switch (i) {
	case 0:
		Twidth += 5;
		break;
	case 1:
		Tlength += 5;
		break;
	case 2:
		Theight += 5;
		break;
	}
}

void Smtable::decrease(int i) {
	switch (i) {
	case 0:
		Twidth -= 5;
		break;
	case 1:
		Tlength -= 5;
		break;
	case 2:
		Theight -= 5;
		break;
	}
}

void Smtable::draw() {
	ctm = RotateX(theta[0]) * RotateY(theta[1]) * RotateZ(theta[2]);//rotes the cube

	colorcube();

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(quad_color), quad_color);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices); // the top of the table

	//drawling the table legs

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points2);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(quad_color), quad_color2);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points3);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(quad_color), quad_color2);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points4);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(quad_color), quad_color2);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points5);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(quad_color), quad_color2);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

void Smtable::update(){


}