#include "table.h"


typedef Angel::vec4  point4;
typedef Angel::vec4  color4;

table::table() {

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

	tscale = 0;
	width = 315;//135
	length = 5;//
	height = 135;//

	int Twidth = 40;//
	int Tlength = 200;//
	int Theight = 30;//

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
	vertices2[0] = point4(-Twidth, -(Theight), length, 1.0);
	vertices2[1] = point4(-Twidth, (Theight), length, 1.0);
	vertices2[2] = point4(Twidth, (Theight), length, 1.0);
	vertices2[3] = point4(Twidth, -(Theight), length, 1.0);
	vertices2[4] = point4(-Twidth, -(Theight), -Tlength, 1.0);
	vertices2[5] = point4(-Twidth, (Theight), -Tlength, 1.0);
	vertices2[6] = point4(Twidth, (Theight), -Tlength, 1.0);
	vertices2[7] = point4(Twidth, -(Theight), -Tlength, 1.0);

	loc.x = 0;
	loc.y = 0;
	loc.z = 0;
	tloc = Translate(loc.x, loc.y, loc.z);
	calcMatrices();

}



void table::MyQuad(int a, int b, int c, int d) {
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

void table::MyQuad2(int a, int b, int c, int d) {
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
	points2[i] = ctm * vertices2[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = ctm * vertices2[b];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = ctm * vertices2[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = ctm * vertices2[a];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = ctm * vertices2[c];
	i++;
	quad_color[i] = ambient_color + diffuse_color + specular_color;
	points2[i] = ctm * vertices2[d];
	i++;
	i %= 36;


}


void table::colorcube(){
  MyQuad(1,0,3,2);
  MyQuad(2,3,7,6);
  MyQuad(3,0,4,7);
  MyQuad(6,5,1,2);
  MyQuad(4,5,6,7);
  MyQuad(5,4,0,1);

  MyQuad2(1,0,3,2);
  MyQuad2(2,3,7,6);
  MyQuad2(3,0,4,7);
  MyQuad2(6,5,1,2);
  MyQuad2(4,5,6,7);
  MyQuad2(5,4,0,1);
}

void table::changeScale(int i) {

	//the table
	vertices[0] = point4(-(width + tscale), -(height + tscale), (length + tscale), 1.0);
	vertices[1] = point4(-(width + tscale), (height + tscale), (length + tscale), 1.0);
	vertices[2] = point4((width + tscale), (height + tscale), (length + tscale), 1.0);
	vertices[3] = point4((width + tscale), -(height + tscale), (length + tscale), 1.0);
	vertices[4] = point4(-(width + tscale), -(height + tscale), -(length + tscale), 1.0);
	vertices[5] = point4(-(width + tscale), (height + tscale), -(length + tscale), 1.0);
	vertices[6] = point4((width + tscale), (height + tscale), -(length + tscale), 1.0);
	vertices[7] = point4((width + tscale), -(height + tscale), -(length + tscale), 1.0);

	//the base of the table
	vertices2[0] = point4(-(Twidth + tscale), -(Theight + tscale), (Tlength + tscale), 1.0);
	vertices2[1] = point4(-(Twidth + tscale), (Theight + tscale), (Tlength + tscale), 1.0);
	vertices2[2] = point4((Twidth + tscale), (Theight + tscale), (Tlength + tscale), 1.0);
	vertices2[3] = point4((Twidth + tscale), -(Theight + tscale), (Tlength + tscale), 1.0);
	vertices2[4] = point4(-(Twidth + tscale), -(Theight + tscale), -(Tlength + tscale), 1.0);
	vertices2[5] = point4(-(Twidth + tscale), (Theight + tscale), -(Tlength + tscale), 1.0);
	vertices2[6] = point4((Twidth + tscale), (Theight + tscale), -(Tlength + tscale), 1.0);
	vertices2[7] = point4((Twidth + tscale), -(Theight + tscale), -(Tlength + tscale), 1.0);
}

void table::calcMatrices() {
	 tloc = ctm * tloc;
	 model_veiw_top = ctm * tloc;
	  model_veiw_leg = ctm * tloc;
}


void table::increaseScale(){changeScale(tscale+=5);}
void table::decreaseScale(){changeScale(tscale-=5);}

void table::increase(int i) {
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

void table::decrease(int i) {
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

void table::updateModelVeiwTop(){

glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_veiw_top);

}
void table::updateModelVeiwLeg(){

glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_veiw_leg);

}
void table::draw() {
	ctm = RotateX(theta[0]) * RotateY(theta[1]) * RotateZ(theta[2]);
	calcMatrices();
	colorcube();
	// Dpoints = points;// get the 
	// Dpoints2 =points2;
	/*for(int i =0; i < NumVertices;i++){
	 Dpoints[i].x = Dpoints[i].x *(1.0/1000.0);
	Dpoints[i].y = Dpoints[i].y *(1.0/1000.0);
	Dpoints[i].z = Dpoints[i].z *(1.0/1000.0);
	 Dpoints[i].w  =0;
	Dpoints2[i].x = Dpoints2[i].x *(1.0/1000.0);
	Dpoints2[i].y = Dpoints2[i].y *(1.0/1000.0);
	Dpoints2[i].z = Dpoints2[i].z *(1.0/1000.0);
	Dpoints2[i].w  =0;
	}*/
	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_veiw_top);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(quad_color), quad_color);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices); // the top of the table

	glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_veiw_leg);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points2);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices); // the leg of the table


}

void table::update(){


}