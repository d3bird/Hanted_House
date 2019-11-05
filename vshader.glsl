attribute vec4 vPosition;
attribute vec4 vColor;
varying vec4 color;

uniform mat4 Projection;
uniform mat4 model_trans;
uniform mat4 model_view;
void main() 
{


  gl_Position = Projection * model_trans * model_view  * ((vPosition ));
  gl_Position.x = (1.0/1000.0)*(vPosition.x );
  gl_Position.y = (1.0/1000.0)*(vPosition.y );
  gl_Position.z = (1.0/1000.0)*(vPosition.z );
  //gl_Position.w =1.0;
  color = vColor;
} 
