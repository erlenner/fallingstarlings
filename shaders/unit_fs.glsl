#version 300 es
precision mediump float;
smooth in vec4 Color;
out vec4 outColor;
void main()
{
    if(Color.a < 0.5)
        discard;
	outColor = Color;
}
