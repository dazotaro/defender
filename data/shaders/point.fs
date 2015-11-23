#version 420

in vec4 vcolor;
out vec4 outputColor;

uniform sampler2D tex_image;

void main()
{
    outputColor = vcolor * texture(tex_image, gl_PointCoord);   
}
