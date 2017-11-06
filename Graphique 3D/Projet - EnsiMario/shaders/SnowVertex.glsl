#version 330

uniform mat4 projMat, viewMat, modelMat;

in vec3 vPosition;
in vec4 vColor;


out vec4 fragmentColor; 

void main()
{
    fragmentColor  = vColor;
    gl_Position = vec4(vPosition[0]/90.0f, vPosition[1]/50.0f, vPosition[2], 1.0f);
}
