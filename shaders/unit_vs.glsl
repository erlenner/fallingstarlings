#version 300 es
precision mediump float;
layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;
uniform vec2 map_position;
smooth out vec4 Color;
void main()
{
	gl_Position = vec4( position.x - map_position.x,
                        position.y + map_position.y,
                        0.0, 1.0);
	Color = color;
}
