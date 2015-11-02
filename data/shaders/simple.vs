#version 420
layout(location = 0) in vec3 VertexPosition;

uniform mat3 M;
uniform mat3 MV;
uniform vec4 color;

out vec4 vcolor;


void main()
{
    vcolor = color;
    gl_Position = vec4(MV * VertexPosition, 1.0);
}

