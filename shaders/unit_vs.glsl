#version 300 es
precision mediump float;
layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;
uniform vec4 map_info;
smooth out vec4 Color;
void main()
{
    gl_Position = vec4( (position.x - map_info.x) / map_info.z,
                        (map_info.y - position.y) / map_info.w,
                        0.0, 1.0);
    Color = color;
}
