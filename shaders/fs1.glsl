#version 300 es
precision mediump float;
smooth in vec4 theColor;
out vec4 outputColor;
void main()
{
    if(theColor.a < 0.5)
        discard;
	outputColor = theColor;
}
