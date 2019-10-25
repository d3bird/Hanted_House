attribute vec4 vPosition;
attribute vec4 vColor;
varying vec4 color;
void main() 
{

  gl_Position.x = (1.0/1000.0)*(vPosition.x);
  gl_Position.y = (1.0/1000.0)*(vPosition.y);
  gl_Position.z = (1.0/1000.0)*(vPosition.z);

  //gl_Position = vPosition;
  color = vColor;
} 
