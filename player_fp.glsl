#version 130

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 color_interp;
in vec3 light_pos;

void main() 
{
	gl_FragColor = color_interp;
}
