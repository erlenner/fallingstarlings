#version 300 es
precision mediump float;
layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;
smooth out vec4 theColor;
void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
	theColor = color;
}
