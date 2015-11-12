#version 420

in vec4 vcolor;
out vec4 outputColor;

void main()
{
    outputColor = vcolor;
    //outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);;
}
