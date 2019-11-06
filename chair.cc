#include "chair.h"


typedef Angel::vec4  point4;
typedef Angel::vec4  color4;

chair::chair() {

	theta[0] = 90.0;
	theta[1] = 0.0;
	theta[2] = 0.0;

	material_ambient = color4(1.0, 0.0, 1.0, 1.0);
	material_diffuse = color4(0.0, 0.8, 1.0, 1.0); // color of the chair
	material_specular = color4(1.0, 0.8, 0.0, 1.0);
	material_shininess = 100.0;
	light_position = point4(0.0, 200.0, 1.0, 0.0);
	light_ambient = color4(0.2, 0.2, 0.2, 1.0);
	light_diffuse = color4(1.0, 1.0, 1.0, 1.0);
	light_specular = color4(1.0, 1.0, 1.0, 1.0);
	viewer = vec4(0.0, 0.0, -1.0, 0.0);
	spec = true;

	scale = 0;
	//for the base of the table
	width = 135;//315
	length = 5;//
	height = 135;//

   //for the legs of the table
	Twidth = 10;//
	Tlength = 150;//
	Theight = 10;// not really the height but one of the dim of the sides


	 //for the back of the chair
	Bwidth = 10;//
	Blength = 200;//
	Bheight = 10;//

	loc.x = 1;
	loc.y = 1;
	loc.z = 1;

	special = false;

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


	vertices2[0] = point4(-Twidth, -(Theight), Tlength, 1.0);
	vertices2[1] = point4(-Twidth, (Theight), Tlength, 1.0);
	vertices2[2] = point4(Twidth, (Theight), Tlength, 1.0);
	vertices2[3] = point4(Twidth, -(Theight), Tlength, 1.0);

	vertices2[4] = point4(-Twidth, -(Theight), -length, 1.0);
	vertices2[5] = point4(-Twidth, (Theight), -length, 1.0);
	vertices2[6] = point4(Twidth, (Theight), -length, 1.0);
	vertices2[7] = point4(Twidth, -(Theight), -length, 1.0);


	//the back of the chair

	vertices3[0] = point4(-Bwidth, -(Bheight), length, 1.0);
	vertices3[1] = point4(-Bwidth, (Bheight), length, 1.0);
	vertices3[2] = point4(Bwidth, (Bheight), length, 1.0);
	vertices3[3] = point4(Bwidth, -(Bheight), length, 1.0);

	vertices3[4] = point4(-Bwidth, -(Bheight), -Blength, 1.0);
	vertices3[5] = point4(-Bwidth, (Bheight), -Blength, 1.0);
	vertices3[6] = point4(Bwidth, (Bheight), -Blength, 1.0);
	vertices3[7] = point4(Bwidth, -(Bheight), -Blength, 1.0);

	tloc = Translate(loc.x, loc.y, loc.z);// the location of the table

	BLleg = Translate(width, height, 0);
	BRleg = Translate(-width, -height, 0);

	FLleg = Translate(-width, height, 0);
	RRleg = Translate(width, -height, 0);


	back1 = Translate(width, -(height / 2), 0);
	back2 = Translate(-(width / 2), -height, 0);


}

void chair::setLoc(vec3 i){
	loc = i;
	tloc = Translate(loc.x, loc.y, loc.z);
}
void chair::moveleg(int i) {

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


void chair::MyQuad(int a, int b, int c, int d) {
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
	points[i] = model_veiw_base * vertices[a];// for the table base
	points2[i] = model_veiw_leg1 * vertices2[a];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[a];
	points4[i] = model_veiw_leg3 * vertices2[a];
	points5[i] = model_veiw_leg4 * vertices2[a];
	points6[i] = model_veiw_back1 * vertices3[a];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points[i] = model_veiw_base * vertices[b];// for the table base
	points2[i] = model_veiw_leg1 * vertices2[b];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[b];
	points4[i] = model_veiw_leg3 * vertices2[b];
	points5[i] = model_veiw_leg4 * vertices2[b];
	points6[i] = model_veiw_back1 * vertices3[b];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[b];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points[i] = model_veiw_base * vertices[c];// for the table base
	points2[i] = model_veiw_leg1 * vertices2[c];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[c];
	points4[i] = model_veiw_leg3 * vertices2[c];
	points5[i] = model_veiw_leg4 * vertices2[c];
	points6[i] = model_veiw_back1 * vertices3[c];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points[i] = model_veiw_base * vertices[a];// for the table base
	points2[i] = model_veiw_leg1 * vertices2[a];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[a];
	points4[i] = model_veiw_leg3 * vertices2[a];
	points5[i] = model_veiw_leg4 * vertices2[a];
	points6[i] = model_veiw_back1 * vertices3[a];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points[i] = model_veiw_base * vertices[c];// for the table base
	points2[i] = model_veiw_leg1 * vertices2[c];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[c];
	points4[i] = model_veiw_leg3 * vertices2[c];
	points5[i] = model_veiw_leg4 * vertices2[c];
	points6[i] = model_veiw_back1 * vertices3[c];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points[i] = model_veiw_base * vertices[d];// for the table base
	points2[i] = model_veiw_leg1 * vertices2[d];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[d];
	points4[i] = model_veiw_leg3 * vertices2[d];
	points5[i] = model_veiw_leg4 * vertices2[d];
	points6[i] = model_veiw_back1 * vertices3[d];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[d];
	i++;
	i %= 36;


}
// does the lighting for the legs
void chair::MyQuad2(int a, int b, int c, int d) {
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
	points2[i] = model_veiw_leg1 * vertices2[a];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[a];
	points4[i] = model_veiw_leg3 * vertices2[a];
	points5[i] = model_veiw_leg4 * vertices2[a];
	points6[i] = model_veiw_back1 * vertices3[a];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = model_veiw_leg1 * vertices2[b];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[b];
	points4[i] = model_veiw_leg3 * vertices2[b];
	points5[i] = model_veiw_leg4 * vertices2[b];
	points6[i] = model_veiw_back1 * vertices3[b];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[b];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = model_veiw_leg1 * vertices2[c];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[c];
	points4[i] = model_veiw_leg3 * vertices2[c];
	points5[i] = model_veiw_leg4 * vertices2[c];
	points6[i] = model_veiw_back1 * vertices3[c];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = model_veiw_leg1 * vertices2[a];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[a];
	points4[i] = model_veiw_leg3 * vertices2[a];
	points5[i] = model_veiw_leg4 * vertices2[a];
	points6[i] = model_veiw_back1 * vertices3[a];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = model_veiw_leg1 * vertices2[c];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[c];
	points4[i] = model_veiw_leg3 * vertices2[c];
	points5[i] = model_veiw_leg4 * vertices2[c];
	points6[i] = model_veiw_back1 * vertices3[c];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = model_veiw_leg1 * vertices2[d];//for the chair legs
	points3[i] = model_veiw_leg2 * vertices2[d];
	points4[i] = model_veiw_leg3 * vertices2[d];
	points5[i] = model_veiw_leg4 * vertices2[d];
	points6[i] = model_veiw_back1 * vertices3[d];//for the chair back
	points7[i] = model_veiw_back2 * vertices3[d];
	i++;
	i %= 36;

}

void chair::MyQuad3(int a, int b, int c, int d) {
	static int i = 0;
	// Compute normal vector.
	vec3 n1 = normalize(cross(ctm * vertices3[b] - ctm * vertices3[a], ctm * vertices3[c] - ctm * vertices3[b]));
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
	points6[i] = model_veiw_back1 * vertices3[a];
	points7[i] = model_veiw_back2 * vertices3[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points6[i] = model_veiw_back1 * vertices3[b];
	points7[i] = model_veiw_back2 * vertices3[b];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points6[i] = model_veiw_back1 * vertices3[c];
	points7[i] = model_veiw_back2 * vertices3[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points6[i] = model_veiw_back1 * vertices3[a];
	points7[i] = model_veiw_back2 * vertices3[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points6[i] = model_veiw_back1 * vertices3[c];
	points7[i] = model_veiw_back2 * vertices3[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points6[i] = model_veiw_back1 * vertices3[d];
	points7[i] = model_veiw_back2 * vertices3[d];
	i++;
	i %= 36;

}


void chair::colorcube() {
	MyQuad(1, 0, 3, 2);
	MyQuad(2, 3, 7, 6);
	MyQuad(3, 0, 4, 7);
	MyQuad(6, 5, 1, 2);
	MyQuad(4, 5, 6, 7);
	MyQuad(5, 4, 0, 1);

	/*
	MyQuad2(1,0,3,2);
	MyQuad2(2,3,7,6);
	MyQuad2(3,0,4,7);
	MyQuad2(6,5,1,2);
	MyQuad2(4,5,6,7);
	MyQuad2(5,4,0,1);

	MyQuad3(1,0,3,2);
	MyQuad3(2,3,7,6);
	MyQuad3(3,0,4,7);
	MyQuad3(6,5,1,2);
	MyQuad3(4,5,6,7);
	MyQuad3(5,4,0,1);*/

}

void chair::changeScale(int i) {

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

void chair::increaseScale(){changeScale(scale+=5);}
void chair::decreaseScale(){changeScale(scale-=5);}

void chair::increase(int i) {
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

void chair::calTranMat() {
	model_veiw_base = ctm * tloc;

	model_veiw_leg1 = ctm * tloc * BLleg;
	model_veiw_leg2 = ctm * tloc * BRleg;
	model_veiw_leg3 = ctm * tloc * FLleg;
	model_veiw_leg4 = ctm * tloc * RRleg;

	model_veiw_back1 = ctm * tloc * back1;
	model_veiw_back2 = ctm * tloc * back2;
}

void chair::decrease(int i) {
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

void chair::draw() {
	ctm = RotateX(theta[0]) * RotateY(theta[1]) * RotateZ(theta[2]);//rotes the cube
	calTranMat();
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

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points6);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(quad_color), quad_color2);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points7);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(quad_color), quad_color2);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

void chair::update(){


}