#version 420
layout(location = 0) in vec3 VertexPosition;

uniform mat3 M;
uniform mat3 MV;


void main()
{
   gl_Position = vec4(MV * VertexPosition, 1.0);
}

