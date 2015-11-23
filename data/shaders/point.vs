#version 420
layout(location = 0) in vec2 VertexPosition;
layout(location = 1) in vec4 color;

uniform mat3 V;

out vec4 vcolor;


void main()
{
    vcolor = color;
    gl_Position = vec4(V * vec3(VertexPosition, 1.0), 1.0);
}

