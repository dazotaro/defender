#version 420
layout(location = 0) in vec3 VertexPosition;

uniform mat3 V;
uniform vec4 color;

out vec4 vcolor;


void main()
{
    vcolor = color;
    gl_Position = vec4(V * VertexPosition, 1.0);
}

