#version 420

in vec4 vcolor;
in vec2 vtexcoordinates;
out vec4 outputColor;

uniform sampler2D tex_image;

void main()
{
    outputColor = texture(tex_image, vtexcoordinates);   
    //outputColor = vcolor;
}
