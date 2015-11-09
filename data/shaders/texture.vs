#version 420
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 TexCoordinates;

uniform mat3 M;
uniform mat3 MV;
uniform vec4 color;

out vec4 vcolor;
out vec2 vtexcoordinates;


void main()
{
    vcolor = color;
    vtexcoordinates = TexCoordinates;
    gl_Position = vec4(MV * VertexPosition, 1.0);
}

