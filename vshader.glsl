attribute vec4 vPosition;
attribute vec4 vColor;
varying vec4 color;

uniform mat4 Projection;
uniform mat4 model_trans;
uniform mat4 model_view;
void main() 
{


  
  vPosition.x = (1.0/1000.0)*(vPosition.x );
  vPosition.y = (1.0/1000.0)*(vPosition.y );
  vPosition.z = (1.0/1000.0)*(vPosition.z );

  gl_Position =Projection* model_view  * ((vPosition ));

 // gl_Position.w =1.0;
  color = vColor;
} 
