#version 130

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 color_interp;
in vec3 light_pos;

// Material attributes (constants)
vec4 ambient_color = vec4(0.1, 0.1, 0.1, 1.0);
vec4 diffuse_color = vec4(0.5, 0.5, 0.5, 1.0);
vec4 specular_color = vec4(0.8, 0.5, 0.9, 1.0);
float phong_exponent = 128.0;
float ambient_amount = 0.1;

void main() 
{
	vec3 N, // Interpolated normal for fragment
         L, // Light-source direction
         V, // View direction
         H; // Half-way vector

	gl_FragColor = color_interp;
}
