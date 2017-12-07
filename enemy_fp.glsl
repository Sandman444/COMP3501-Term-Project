#version 130

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 color_interp;
in vec3 light_pos1;
in vec3 light_pos2;

// Material attributes (constants)
vec4 ambient_color = vec4(0.1, 0.0, 0.0, 1.0);
vec4 diffuse_color = vec4(0.5, 0.0, 0.0, 1.0);
vec4 specular_color = vec4(0.5, 0.9, 0.8, 1.0);
float phong_exponent = 32.0;

void main() 
{
	//Phong shading

    vec3 N, // Interpolated normal for fragment
         L1, // Light-source direction
		 L2, //2nd light-source direction
         V, // View direction
         R1,
		 R2; // Reflected light vector

    // Compute Lambertian lighting Id
    N = normalize(normal_interp);

	//Compute lighting direction
    L1 = (light_pos1 - position_interp);
    L1 = normalize(L1);
	L2 = (light_pos2 - position_interp);
    L2 = normalize(L2);

    float Id1 = max(dot(N, L1), 0.0);
	float Id2 = max(dot(N, L2), 0.0);
    
    // Compute specular term for Phong shading Is
    // V = (eye_position - position_interp);
    V = - position_interp; // Eye position is (0, 0, 0) in view coordinates
    V = normalize(V);

	//Compute light reflection
	R1 = -L1 + 2 * dot(L1, N)*N;
	R1 = normalize(R1);
	R2 = -L2 + 2 * dot(L2, N)*N;
	R2 = normalize(R2);

    float spec_angle_cos1 = max(dot(V, R1), 0.0);
    float Is1 = pow(spec_angle_cos1, phong_exponent);
    float spec_angle_cos2 = max(dot(V, R2), 0.0);
    float Is2 = pow(spec_angle_cos2, phong_exponent); 

	// Assign light to the fragment
    gl_FragColor = ambient_color + Id1*diffuse_color + Is1*specular_color + Id2*diffuse_color + Is2*specular_color;
}